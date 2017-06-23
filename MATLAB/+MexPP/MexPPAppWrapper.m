classdef MexPPAppWrapper < handle
    %MEXPPAPPWRAPPER 
    
    % TODO: add list of class names
    properties
        app_name
        all_objects
    end
    
    methods (Static)
        function out = setgetAllWrappers(data)
            persistent all_app_wrappers
            
            if nargin
                all_app_wrappers = data;
            end
            
            if isempty(all_app_wrappers)
                all_app_wrappers = containers.Map('KeyType', 'char', 'ValueType', 'any');
            end
            
            out = all_app_wrappers;
            
        end
        
        function out = setgetLog(varargin)
            persistent log_list
            
            if isempty(log_list)
                log_list = {};
            end
            
            if nargin
                log_list{end+1} = varargin;
            end
            
            out = log_list;
        end
        
        function appWrapperObj = getAppWrapper(app_name)
            all_app_wrappers = MexPP.MexPPAppWrapper.setgetAllWrappers();
            
            if ~all_app_wrappers.isKey(app_name)
                all_app_wrappers(app_name) = MexPP.MexPPAppWrapper(app_name);
            end
            appWrapperObj = all_app_wrappers(app_name);
            
            MexPP.MexPPAppWrapper.setgetAllWrappers(all_app_wrappers);
        end
        
        function objHandle = staticCreateObject(app_name, class_name, varargin)
            app_wrapper = MexPP.MexPPAppWrapper.getAppWrapper(app_name);
            objHandle = app_wrapper.createObject(class_name, varargin{:});
        end
        
        function clearMex()
            all_app_wrappers = MexPP.MexPPAppWrapper.setgetAllWrappers();
            
            all_active_apps = all_app_wrappers.keys;
            for i=1:length(all_active_apps)
                app_wrapper = all_app_wrappers(all_active_apps{i});
                app_wrapper.closeAll();
            end
            
            MexPP.MexPPAppWrapper.setgetAllWrappers([]);
            clear mex;
        end
    end
    
    methods
        function obj = MexPPAppWrapper(app_name)
            % app_name dhould be a string from which we would construct the
            % handle
            obj.app_name = str2func(app_name);
            obj.all_objects = containers.Map('KeyType', 'uint64', 'ValueType', 'any');
        end
        
        function varargout = runCommand(obj, class_name, func_name, varargin)
            [varargout{1:nargout}] = obj.app_name(class_name, func_name, varargin{:});
            MexPP.MexPPAppWrapper.setgetLog(class_name, func_name, varargin, varargout);
        end
        
        function objHandle = createObject(obj, class_name, varargin)
            hndl_id = obj.runCommand(class_name, 'New', varargin{:});
            objHandle = MexPP.MexPPObjectWrapper(class_name, hndl_id, obj);
            obj.all_objects(hndl_id) = objHandle;
        end
        
        function deleteObj(obj, hndl_id)
            objHandle = obj.all_objects(hndl_id);
            obj.runCommand(objHandle.getClassName(), 'Delete', hndl_id);
            obj.all_objects.remove(hndl_id);
        end
        
        function hndl_id = restoreObject(obj, mex_obj_hndl)
            hndl_id = obj.runCommand(mex_obj_hndl.class_name, 'Restore', mex_obj_hndl.getSavedState());
            obj.all_objects(hndl_id) = mex_obj_hndl;
        end
        
        function app_name = getAppName(obj)
            app_name = obj.app_name;
        end
        
        function closeAll(obj)
            all_active_hndls = obj.all_objects.keys;
            for i=1:length(all_active_hndls)
                curr_obj = obj.all_objects(all_active_hndls{i});
                curr_obj.disconnect();
            end
        end
    end
    
end

