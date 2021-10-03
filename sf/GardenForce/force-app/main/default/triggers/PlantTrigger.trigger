/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 10-03-2021
 * @last modified by  : Matias Kruk
**/
trigger PlantTrigger on Plant__c (after insert, after update) {
    for (Plant__c plant: Trigger.new){
        PlantTriggerHandler.updateParameters(plant.PlantId__c, Integer.valueOf(plant.moist__c), Integer.valueOf(plant.refresh__c), Integer.valueOf(plant.flowMS__c));
    }
}