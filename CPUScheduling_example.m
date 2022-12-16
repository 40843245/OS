clear
clc

cpu=CPUScheduling([24 3 3],4);
cpu=cpu.FCFS();
cpu=cpu.SJF();
cpu=cpu.RR();
cpu