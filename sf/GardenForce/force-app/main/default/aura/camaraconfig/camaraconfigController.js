/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 10-09-2021
 * @last modified by  : Matias Kruk
**/
({
    doInit : function(component, event, helper) {
        let action=  component.get('c.getCameraUrl');  // Calling apex method
        let recordId = component.get('v.recordId');
        action.setParams({ recordId: recordId });
        action.setCallback(this,function(response) {
                var state=response.getState();            // getting the state
                if(state==='SUCCESS')
                {
                    let cameraUrl = response.getReturnValue();    // setting the value in attribute
                    var newMapAttributes = {"src": cameraUrl};
                    component.find("imgDiv").set("v.HTMLAttributes",newMapAttributes);
                }
        });
        $A.enqueueAction(action);
    }
})
