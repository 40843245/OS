classdef ProcessPartition
    properties
        process
        partition
        curr_process_pointer
        curr_partition_pointer
        First_Fit_isExist
        First_Fit_isBack
        First_Fit_Process_queue
        First_Fit_Partition_queue
        First_Fit_Matrix
      
        Best_Fit_isExist
        Best_Fit_isBack
        Best_Fit_Process_queue
        Best_Fit_Partition_queue
        Best_Fit_Matrix
        
        Worst_Fit_isExist
        Worst_Fit_isBack
        Worst_Fit_Process_queue
        Worst_Fit_Partition_queue
        Worst_Fit_Matrix
    end
    methods(Access=public)
        
        %constructor
        function obj=ProcessPartition(proc,part)
            obj.process=proc;
            obj.partition=part;
        end

        %first fit
        %the first partition which is greater than or equal to the need
        %of process will be matched.
        function obj=First_Fit(obj)
            obj.curr_process_pointer=1;
            obj.curr_partition_pointer=1;
            obj.First_Fit_Process_queue=obj.process;
            obj.First_Fit_Partition_queue=obj.partition;
            obj.First_Fit_isExist=logical(false);
            obj.First_Fit_isBack=logical(false);
            isContinue=logical(true);

            
            while isContinue==logical(true)
                currProcess=obj.First_Fit_Process_queue(obj.curr_process_pointer);
                currPartition=obj.First_Fit_Partition_queue(obj.curr_partition_pointer);
                if currProcess<=currPartition
                    %remove the obj.curr_partition_pointer element.
                    obj.First_Fit_Process_queue=Dequeue(obj.First_Fit_Process_queue,obj.curr_process_pointer);
                    obj.First_Fit_Partition_queue=Dequeue(obj.First_Fit_Partition_queue,obj.curr_partition_pointer);
                    obj.First_Fit_isBack=logical(false);
                else
                    obj.curr_partition_pointer=obj.curr_partition_pointer+1;
                end

                %all process are partitioned
                if  isempty(obj.First_Fit_Process_queue)
                    isContinue=logical(false);
                    obj.First_Fit_isExist=logical(true);
                end
                
                if obj.curr_partition_pointer>length(obj.First_Fit_Partition_queue)
                    if obj.First_Fit_isBack==logical(true)
                        obj.First_Fit_isExist=logical(false);
                        isContinue=logical(false);
                    end
                    obj.First_Fit_isBack=logical(true);
                    obj.curr_partition_pointer=1;
                end
            end
            return;

            function queue=Dequeue(queue,pos)
                queue(pos)=[];
                return;
            end
        end

        %best fit
        %smaller partition which is greater than the need of process have
        %higher priority for matching
        function obj=Best_Fit(obj)
            %initialize
            obj.curr_process_pointer=1;
            obj.curr_partition_pointer=1;
            obj.Best_Fit_Process_queue=obj.process;
            obj.Best_Fit_Partition_queue=obj.partition;
            obj.Best_Fit_isExist=logical(false);
            obj.Best_Fit_isBack=logical(false);
            isContinue=logical(true);

      
            while isContinue==logical(true)
  
                currProcess=obj.Best_Fit_Process_queue(obj.curr_process_pointer);
                
                lens=length(obj.Best_Fit_Partition_queue);
                cnt=1;
                minVal=max(obj.Best_Fit_Partition_queue)+1;
                minIndex=-1;
                isLoop=logical(true);
                
                %-1 for fixed 
                obj.curr_partition_pointer=obj.curr_partition_pointer-1;
                while isLoop==logical(true)
                    obj.curr_partition_pointer=mod(obj.curr_partition_pointer,lens)+1;
                    currPartition=obj.Best_Fit_Partition_queue(obj.curr_partition_pointer);
                    if currProcess<=currPartition
                        %Is currParition smaller
                        if minVal>currPartition
                            minVal=currPartition;
                            minIndex=obj.curr_partition_pointer;
                        end
                    end                 
                    if  cnt>=(lens+1)
                        isLoop=logical(false);
                    end
                    cnt=cnt+1;
                end
                        
                %check there exist fit partition.
                if minIndex==-1
                    isContinue=logical(false);
                    obj.Best_Fit_isExist=logical(false);
                    break;
                end

                %dequeue
                obj.Best_Fit_Process_queue=Dequeue(obj.Best_Fit_Process_queue,obj.curr_process_pointer);
                obj.Best_Fit_Partition_queue=Dequeue(obj.Best_Fit_Partition_queue,minIndex);
                
                %check visit of every elements in Best_Fit_Process_queue
                if  isempty(obj.Best_Fit_Process_queue)
                    isContinue=logical(false);
                    obj.Best_Fit_isExist=logical(true);
                    break;
                end
            end
            return;

            function queue=Dequeue(queue,pos)
                queue(pos)=[];
                return;
            end
        end

        %worst fit
        %biggest parition have higher priority for matching.
        function obj=Worst_Fit(obj)

            obj.curr_process_pointer=1;
            obj.curr_partition_pointer=1;
            obj.Worst_Fit_Process_queue=obj.process;
            obj.Worst_Fit_Partition_queue=obj.partition;
            lens=length(obj.process);
            cnt=1;
            isContinue=logical(true);
            while isContinue==logical(true)
                currProcess=obj.process(obj.curr_process_pointer);
                [currPartition,maxIndex]=max(obj.Worst_Fit_Partition_queue);
                if currProcess<currPartition
                    obj.Worst_Fit_Process_queue=Dequeue(obj.Worst_Fit_Process_queue,obj.curr_process_pointer);
                    obj.Worst_Fit_Partition_queue=Dequeue(obj.Worst_Fit_Partition_queue,maxIndex);
                else
                    obj.Worst_Fit_isExist=logical(false);
                    %isContinue=false; %this comment is for executing the
                    %while loop.
                end

                if isempty(obj.Worst_Fit_Partition_queue)
                    obj.Worst_Fit_isExist=logical(true);
                    isContinue=false;
                end
                
                cnt=cnt+1;
                %check the visit for all process.
                if cnt>=(lens+1)
                    obj.Worst_Fit_isExist=logical(false);
                    isContinue=false;
                end

                obj.curr_process_pointer=obj.curr_process_pointer+1;
                obj.curr_partition_pointer=mod(obj.curr_partition_pointer,length(obj.partition))+1;
            end
            return;

            function queue=Dequeue(queue,pos)
                queue(pos)=[];
                return;
            end
        end
    end
end