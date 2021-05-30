/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 05-29-2021
 * @last modified by  : Matias Kruk
 * Modifications Log 
 * Ver   Date         Author        Modification
 * 1.0   05-29-2021   Matias Kruk   Initial Version
**/
public with sharing class PlanReportApex {
    @AuraEnabled(cacheable=true)
    public static List<SObject> getMoistureHistory(ID plantID, String fecha){
        try {
            Integer day = Integer.valueOf(fecha.split('-')[2]);
            Integer month = Integer.valueOf(fecha.split('-')[1]);
            Integer year = Integer.valueOf(fecha.split('-')[0]);
            return [SELECT CreatedDate, NewValue
            FROM Plant__History
            WHERE Field = 'current__c' AND ParentId = :plantID AND DAY_IN_MONTH(CreatedDate) = :day AND CALENDAR_MONTH(CreatedDate) = :month AND CALENDAR_YEAR(CreatedDate) = :year
             ORDER BY CreatedDate DESC
            LIMIT 200
            ];
        } catch (Exception e) {
            throw new AuraHandledException(e.getMessage());
        }
    }
}
