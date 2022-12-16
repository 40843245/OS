classdef DiskScheduling
    properties
        Disk_Process
        Disk_Starter
        Disk_EndLine
    end
    methods (Access=public)
        function obj=DiskScheduling(proc,endline)
            obj.Disk_Process=proc;
            obj.Disk_EndLine=endline;
            return;
        end
        function dist=FCFS(obj,starter)
            obj.Disk_Starter=starter;
            lens=length(obj.Disk_Process);
            dist=abs(obj.Disk_Process(1)-starter);
            for idx=[2:1:lens]
                currDist=obj.Disk_Process(idx)-obj.Disk_Process(idx-1);
                dist=dist+abs(currDist);
            end
            return;
        end

        function dist=SCAN(obj,starter)
            currDist=starter;
            [maxVal,maxIndex]=max(obj.Disk_Process);
            currDist=currDist+maxVal;
            dist=currDist;
        end
        function dist=CSCAN(obj,starter)
            currDist=abs(obj.Disk_EndLine-starter);
            [minVal,minIndex]=min(obj.Disk_Process);
            currDist=currDist+abs(obj.Disk_EndLine-minVal);
            dist=currDist;
        end
        function dist=LOOK(obj,starter)
            [minVal,minIndex]=min(obj.Disk_Process);
            [maxVal,maxIndex]=max(obj.Disk_Process);
            currDist=abs(starter-minVal);
            currDist=currDist+abs(maxVal-minVal);
            dist=currDist;
        end

         function dist=CLOOK(obj,starter)
            [minVal,minIndex]=min(obj.Disk_Process);
            [maxVal,maxIndex]=max(obj.Disk_Process);
            currDist=abs(maxVal-starter);
            currDist=currDist+abs(minVal-maxVal);
            dist=currDist;
        end
    end
end