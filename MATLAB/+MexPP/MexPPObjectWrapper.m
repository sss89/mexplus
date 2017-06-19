classdef MexPPObjectWrapper < handle
    %MEXPPOBJECTWRAPPER Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        class_name
        mex_handle
        id
        saved_state
        AppWrapper
    end
    
    methods
        function obj = MexPPObjectWrapper(class_name, mex_handle, AppWrapper)
            obj.class_name = class_name;
            obj.mex_handle = mex_handle;
            obj.AppWrapper = AppWrapper;
            obj.saved_state = [];
            obj.id = mex_handle;
        end
        
        function varargout = runCommand(obj, func_name, varargin)
            [varargout{1:nargout}] = obj.AppWrapper.runCommand(obj.class_name, func_name, obj.mex_handle, varargin{:});
        end
        
        function delete(obj)
            obj.AppWrapper.deleteObj(obj.mex_handle);
        end
        
        function disconnect(obj)
            if ~isempty(obj.mex_handle)
                obj.saved_state = obj.runCommand('Serialize');
                obj.AppWrapper.deleteObj(obj.mex_handle);
                obj.mex_handle = [];
            end
        end
        
        function id = getID(obj)
            id = obj.id;
        end
        
        function restoreConnection(obj)
            if isempty(obj.mex_handle)
                obj.mex_handle = obj.AppWrapper.restoreObject(obj);
            end
        end
        
        function class_name = getClassName(obj)
            class_name = obj.class_name;
        end
        
        function saved_state = getSavedState(obj)
            saved_state = obj.saved_state;
        end
    end
    
end

