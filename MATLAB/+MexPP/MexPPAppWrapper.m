classdef MexPPAppWrapper < handle
    %MEXPPAPPWRAPPER 
    
    % TODO: add list of class names
    properties
        app_name
        all_objects
    end
    
    methods
        function obj = MexPPAppWrapper(app_name)
            obj.app_name = app_name;
            obj.all_objects = containers.Map('KeyType', 'uint64', 'ValueType', 'any');
        end
        
        function varargout = runCommand(obj, class_name, func_name, varargin)
            [varargout{1:nargout}] = obj.app_name(class_name, func_name, varargin{:});
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
            hndl_id = obj.runCommand(mex_obj_hndl.class_name, 'Restore', mex_obj_hndl.saved_data);
            obj.all_objects(hndl_id) = mex_obj_hndl;
        end
    end
    
end

