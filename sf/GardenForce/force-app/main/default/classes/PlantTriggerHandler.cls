/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 10-03-2021
 * @last modified by  : Matias Kruk
**/
public with sharing class PlantTriggerHandler {
    @future(callout=true)
    public static void updateParameters(String plantId, Integer plantMoist, Integer plantReadMs, Integer plantFlowMs) {
        
        RefreshPlantParametersCallout.updatePlantMoist(plantId, plantMoist);
        RefreshPlantParametersCallout.updatePlantReadMs(plantId, plantReadMs);
        RefreshPlantParametersCallout.updatePlantFlowMS(plantId, plantFlowMs);
    }
}
