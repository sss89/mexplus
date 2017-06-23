classdef MexPPObjectWrapper < matlab.mixin.Copyable
    %MEXPPOBJECTWRAPPER Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        class_name
        mex_handle
%         id
        saved_state
        AppWrapper
    end
    
    methods(Access = protected)
        % Override copyElement method:
        function cpObj = copyElement(obj)
            to_restore = ~isempty(obj.mex_handle);
            
            obj.disconnect();
            cpObj = copyElement@matlab.mixin.Copyable(obj);
            
            if to_restore
                obj.restoreConnection();
                cpObj.restoreConnection();
            end
        end
    end
    
    methods (Static)
        function obj = loadobj(s)
            obj.AppWrapper = MexPP.MexPPAppWrapper.getAppWrapper(s.app_name);
            obj.class_name = s.class_name;
            obj.saved_state = s.saved_state;
            obj.mex_handle = [];
            if s.is_connected
                obj.restoreConnection();
            end
        end
        
    end
   
    methods
        function s = saveobj(obj)
            s = struct();
            s.app_name = obj.AppWrapper.getAppName();
            s.class_name = obj.class_name;
            s.saved_state = obj.getSavedState();
            s.is_connected = ~isempty(obj.mex_handle);
        end
        
        function obj = MexPPObjectWrapper(class_name, mex_handle, AppWrapper)
            obj.class_name = class_name;
            obj.mex_handle = mex_handle;
            obj.AppWrapper = AppWrapper;
            obj.saved_state = [];
%             obj.id = mex_handle;
        end
        
        function varargout = runCommand(obj, func_name, varargin)
            [varargout{1:nargout}] = obj.AppWrapper.runCommand(obj.class_name, func_name, obj.mex_handle, varargin{:});
        end
        
        function delete(obj)
            if ~isempty(obj.mex_handle)
                obj.AppWrapper.deleteObj(obj.mex_handle);
            end
        end
        
        function disconnect(obj)
            obj.saved_state = obj.getSavedState();
            if ~isempty(obj.mex_handle)
                obj.AppWrapper.deleteObj(obj.mex_handle);
                obj.mex_handle = [];
            end
        end
%         
%         function id = getID(obj)
%             id = obj.id;
%         end
        
        function restoreConnection(obj)
            if isempty(obj.mex_handle)
                obj.mex_handle = obj.AppWrapper.restoreObject(obj);
            end
        end
        
        function class_name = getClassName(obj)
            class_name = obj.class_name;
        end
        
        function saved_state = getSavedState(obj)
            if ~isempty(obj.mex_handle)
                obj.saved_state = obj.runCommand('Serialize');
            end
            saved_state = obj.saved_state;
        end
        
        
    end
    
end

