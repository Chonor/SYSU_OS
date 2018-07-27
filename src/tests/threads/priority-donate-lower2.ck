# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(priority-donate-lower2) begin
(priority-donate-lower2) Main thread create a thread have priority 30.
(priority-donate-lower2) Main thread have priority 31 and sleep 10 ticks.
(priority-donate-lower2) a: begin try acquire lcok and it have priority 30.
(priority-donate-lower2) Main thread awake and set the priority = 20.
(priority-donate-lower2) Main thread should have priority 30.  Actual priority: 30.
(priority-donate-lower2) Main thread should have priority 30.  Actual priority: 30.
(priority-donate-lower2) a: got the lock.
(priority-donate-lower2) a: done.
(priority-donate-lower2) b: done.
(priority-donate-lower2) Main thread should have priority 20.  Actual priority: 20.
(priority-donate-lower2) a , b must already have finished.
(priority-donate-lower2) end
EOF
pass;