%RAG(Resource-Allocation Graph)
classdef RAG
    properties
        numOfProcess
        numOfThread
        allocation
        max_allocation
        available
        need
        safestate
        work
        finish
        CanBeRequested
        curr_pointer
        vector_le
    end
    methods(Access=public) 
        %constructor
        function obj=RAG(allocation,max_allocation,available)
            obj.allocation=allocation;
            obj.max_allocation=max_allocation;
            obj.available=available;
            obj.need=obj.max_allocation-obj.allocation;
            siz=size(obj.allocation);
            obj.numOfThread=siz(1);
            obj.numOfProcess=siz(2);
            obj.finish=zeros([1 obj.numOfThread]);
            obj.work=obj.available;
            obj.curr_pointer=1;
            obj.CanBeRequested=logical(false);
        end

        function DisplayInfo(obj)
            fprintf("number of Threads:\n");
            obj.numOfThread
            fprintf("number of Processes:\n");
            obj.numOfProcess
            fprintf("allocation:\n");
            obj.allocation
            fprintf("max_allocation:\n");
            obj.max_allocation
            fprintf("available:\n");
            obj.available
            fprintf("need:\n");
            obj.need
            fprintf("finish:\n");
            obj.finish
            fprintf("current work:\n");
            obj.work
        end

        function obj=CheckSafeState(obj)
            %initialize
            obj.finish=zeros([1 obj.numOfThread]);
            obj.work=obj.available;
            obj.curr_pointer=1;

            cnt=0;
            isContinue=logical(true);
            while isContinue==logical(true)
                if obj.finish(obj.curr_pointer)==0
                    currNeed=obj.need(obj.curr_pointer,:);
                    obj=obj.check_vector_le(currNeed,obj.work);
                    if obj.vector_le~=0
                        obj.finish(obj.curr_pointer)=1;
                        obj.work=obj.work+obj.allocation(obj.curr_pointer,:);
                        cnt=0;
                    else
                        cnt=cnt+1;
                    end
                else
                   cnt=cnt+1; 
                end
                
                if cnt>=obj.numOfThread
                    isContinue=logical(false);
                    obj.safestate='unsafe';
                end
                obj.curr_pointer=mod(obj.curr_pointer,obj.numOfThread)+1;

                if all(obj.finish)==logical(true)
                    isContinue=logical(false);
                    obj.safestate='safe';
                end
            end
            return;
         end
        
         function obj=check_vector_le(obj,vec1,vec2)
                obj.vector_le=(sum(vec1<=vec2)==length(vec1));
                return;
         end
         function obj=Request(obj,vec1)
                obj.CanBeRequested=logical(false);
                obj=obj.check_vector_le(vec1,obj.work);
                if obj.vector_le~=0
                    obj.available=obj.available-vec1;
                    tempObj=obj.CheckSafeState();
                    fprintf("---line---\n");
                    T=tempObj
                    fprintf("---end line---\n");
                    if strcmp(tempObj.safestate,'safe')==0
                        obj=tempObj;
                        obj.CanBeRequested=logical(true);
                    end
                end
         end
    end 
end