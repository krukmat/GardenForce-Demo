/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 10-03-2021
 * @last modified by  : Matias Kruk
**/
public with sharing class SchedulePlantBatch  implements Database.Batchable<sObject>, Schedulable, Database.AllowsCallouts{
    public List<Schedule__c> start(Database.BatchableContext bc){
        return [SELECT Plant__r.PlantId__c, number__c FROM Schedule__c WHERE date__c = TODAY];
    }
    public void execute(Database.BatchableContext BC, List<sObject> scope){
        List<Schedule__c> schedules = (List<Schedule__c>) scope;
        for(Schedule__c schedule : schedules){
            if(schedule.Plant__r != null){
                RefreshPlantParametersCallout.hidrate(schedule.Plant__r.PlantId__c, Integer.valueOf(schedule.number__c));
            }
        }
    }
    public void finish(Database.BatchableContext BC){
    }

    public void execute(SchedulableContext ctx){
        Database.executeBatch(new SchedulePlantBatch());
    }

    public static void configureSchedule(){
        SchedulePlantBatch p = new SchedulePlantBatch();
        String sch = '0 10 13 * * ?';
        system.schedule('Hidrate scheduler', sch, p);
    }
}
