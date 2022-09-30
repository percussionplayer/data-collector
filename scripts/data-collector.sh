#!/bin/sh
# Copyright 2022 Frank Ronneburg.  All rights reserved.
#
# data-collector   Start/Stop the Data Collector
#
#

CFG_FILE="/etc/opt/data-collector.cfg"
DATA_COLLECTOR_BIN="data-collector-bin"
SERVICE=`basename "$0"`
MAX_STARTUP_CHECKS=10
MAX_STOP_ATTEMPTS=30


syslog() {
   echo "$@"
   logger -p info -t data-collector "$@"
}


echo_failure() {
   echo "failed";
}


echo_success() {
   echo "success";
}


get_app_pid() {
   pidof $1
}


start_app() {
   local app=$1
   local cfgFile=$2

   if [ -f "/usr/local/bin/$app" ]; then
      /usr/local/bin/$app $cfgFile > /dev/null 2>&1 &
   else
      ./$app $cfgFile > /dev/null 2>&1 &
   fi

   # Wait for the app to come up
   local attempts=0
   local pid=$(get_app_pid $app)
   while [ -z "$pid" ]
   do
      if [ $attempts -gt $MAX_STARTUP_CHECKS ]; then
         break
      fi
      sleep 1
      pid=$(get_app_pid $app)
      attempts=$((attempts+1))
   done
}


start_service() {
   local data_collector_pid=$(get_app_pid $DATA_COLLECTOR_BIN)
   if [ ! -z "$data_collector_pid" ]; then
      echo -n " ($SERVICE is already running:$data_collector_pid)"
      return 1
   else
      start_app $DATA_COLLECTOR_BIN $CFG_FILE
      data_collector_pid=$(get_app_pid $DATA_COLLECTOR_BIN)
      if [ ! -z "$data_collector_pid" ]; then
         return 0
      else
         syslog "Failed to start $DATA_COLLECTOR_BIN"
         return 1
      fi
   fi
}


stop_app() {
   local app=$1
   local pid=$(get_app_pid $app)

   local attempts=0
   while [ ! -z "$pid" ]
   do
      # If we've already tried a bunch of times,
      # just give up and print an error message.
      if [ $attempts -gt $MAX_STOP_ATTEMPTS ] ; then
        return 1
      fi

      kill -INT $pid > /dev/null 2>&1

      sleep 1
      pid=$(get_app_pid $app)
      attempts=$((attempts+1))
   done

   return 0
}


stop_service() {
   stop_app $DATA_COLLECTOR_BIN
}


status_app() {
   # Only check the agent.
   local pid=$(get_app_pid $DATA_COLLECTOR_BIN)
   if [ ! -z "$pid" ]; then
      echo "$SERVICE is running"
      return 0
   else
      echo "$SERVICE is stopped"
      return 1
   fi
}


APP_RC=0

case $1 in
   start)
      echo -n "Starting $SERVICE:"
      start_service
      APP_RC=$?
      if [ "$APP_RC" -gt 0 ]; then
         echo_failure
      else
         echo_success
      fi
      echo
      ;;

   stop)
      echo -n "Stopping $SERVICE:"
      stop_service
      APP_RC=$?
      if [ "$APP_RC" -gt 0 ]; then
         echo_failure
      else
         echo_success
      fi
      echo
      ;;

   status)
      status_app
      APP_RC=$?
      ;;

   restart)
      $0 stop
      $0 start
      APP_RC=$?
      ;;

   *)
      echo "Usage: `basename "$0"` {start|stop|status|restart}"
      exit 1
esac

exit $APP_RC
