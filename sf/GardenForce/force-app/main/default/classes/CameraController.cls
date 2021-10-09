/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 10-09-2021
 * @last modified by  : Matias Kruk
**/
public with sharing class CameraController {
    @AuraEnabled(cacheable=true)
    public static String getCameraUrl(Id recordId) {
        return [SELECT CameraUrl__c FROM Plant__c WHERE Id = :recordId].CameraUrl__c;
    }
}
