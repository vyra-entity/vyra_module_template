#!/bin/bash

openssl req -x509 -newkey rsa:4096 -keyout webserver.key -out webserver.crt -days 3650 -nodes -subj "/CN=modulemanager"