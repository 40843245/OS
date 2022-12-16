clear
clc
%example from OS textbook page 360 CH8-6-3-3 example
allocation    =[0 1 0;2 0 0;3 0 2;2 1 1;0 0 2];
max_allocation=[7 5 3;3 2 2;9 0 2;2 2 2;4 3 3];
available     =[3 3 2];

r=RAG(allocation,max_allocation,available);
r.DisplayInfo();
r=r.Request([1 0 2]);
r=r.CheckSafeState();
r.DisplayInfo();
r
