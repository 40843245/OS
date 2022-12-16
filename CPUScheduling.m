classdef CPUScheduling
    properties
        BurstTime
        numOfProcess
        time_quantum
        tempQueue
        timeQueue
        %FCFS
        FCFS_Time
        FCFS_process
        %SJF
        SJF_Time
        SJF_process
        %RR
        RR_Time
        RR_process
    end
    methods(Access=public)
        %constructor
        function obj=CPUScheduling(BurstTime,time_quantum)
            obj.BurstTime=BurstTime;
            obj.time_quantum=time_quantum;
            obj.numOfProcess=length(obj.BurstTime);
        end
        
        function queue=Push(obj,queue,elem)
            len=length(queue);
            queue(len+1)=elem;
        end

        function queue=Pop_Front(obj,queue)
            queue(1)=[3];
        end
        %FCFS(First-Come Frist-Served)
        function obj=FCFS(obj)
            
            %Get total waiting time
            if obj.numOfProcess>=2
                total=cumsum(obj.BurstTime);
                obj.FCFS_Time(1)=sum(total(1:end-1));
            else
                obj.FCFS_Time(1)=obj.BurstTime(1);
            end
            %Get the mean waiting time.
            obj.FCFS_Time(2)=obj.FCFS_Time(1)/obj.numOfProcess;

            obj.FCFS_process=[1:1:obj.numOfProcess];
            return;
        end

        %SJF(Shortest Job First)
        function obj=SJF(obj)
            obj.SJF_process=sort(obj.BurstTime);
            %Get total waiting time
            if obj.numOfProcess>=2
                total=cumsum(obj.SJF_process);
                obj.SJF_Time(1)=sum(total(1:end-1));
            else
                obj.SJF_Time(1)=obj.SJF_process(1);
            end
            %Get the mean waiting time.
            obj.SJF_Time(2)=obj.SJF_Time(1)/obj.numOfProcess;
            return;
        end
        
        %RR(Round-Robin)
        function obj=RR(obj)
            obj.timeQueue=[];
            obj.tempQueue=obj.BurstTime;

            while ~isempty(obj.tempQueue)
                currProcess=obj.tempQueue(1);
                if currProcess<=obj.time_quantum
                    currTime=currProcess;
                    obj.timeQueue=obj.Pop_Front();
                else
                    currTime=currProcess-obj.time_quantum;
                    obj.tempQueue=obj.Push(obj.tempQueue,currTime);
                    obj.timeQueue=obj.Pop_Front();
                end
            end
            
            return;
        end
    end
end