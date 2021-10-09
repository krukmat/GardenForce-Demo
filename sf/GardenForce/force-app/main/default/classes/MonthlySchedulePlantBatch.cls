/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 10-09-2021
 * @last modified by  : Matias Kruk
**/
public with sharing class MonthlySchedulePlantBatch implements Database.Batchable<sObject>, Schedulable, Database.Stateful, Database.AllowsCallouts{
    private String frequency;

    public MonthlySchedulePlantBatch(String strParam) {
        this.frequency = strParam;
    }
    public List<Schedule__c> start(Database.BatchableContext bc){
        if (this.frequency == null){
            this.frequency = 'Daily';
        }
        return [SELECT Plant__r.PlantId__c, number__c FROM Schedule__c WHERE date__c <= TODAY AND Frequency__c = :this.frequency];
    }
    public void execute(Database.BatchableContext BC, List<sObject> scope){
        List<Schedule__c> schedules = (List<Schedule__c>) scope;
        SchedulePlantHelper.callHidrate(schedules);
    }
    public void finish(Database.BatchableContext BC){
    }

    public void execute(SchedulableContext ctx){
        Database.executeBatch(new MonthlySchedulePlantBatch('Monthly'));
    }

    public static void configureSchedule(){
        MonthlySchedulePlantBatch p = new MonthlySchedulePlantBatch('Monthly');
        String sch = '0 0 14 9 * ?';
        system.schedule('Hidrate monthly scheduler', sch, p);
    }
}
