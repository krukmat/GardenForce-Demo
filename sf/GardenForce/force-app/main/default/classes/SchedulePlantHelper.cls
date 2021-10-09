/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 10-09-2021
 * @last modified by  : Matias Kruk
**/
public with sharing class SchedulePlantHelper {
    public static void callHidrate(List<Schedule__c>schedules) {
        for(Schedule__c schedule : schedules){
            if(schedule.Plant__r != null){
                RefreshPlantParametersCallout.hidrate(schedule.Plant__r.PlantId__c, Integer.valueOf(schedule.number__c));
            }
        }
    }
}
