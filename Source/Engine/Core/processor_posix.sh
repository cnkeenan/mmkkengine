#!/bin/bash

logic_ct=0

logic_ct="$(sysctl -n hw.logicalcpu_max)"

echo "${logic_ct}"
