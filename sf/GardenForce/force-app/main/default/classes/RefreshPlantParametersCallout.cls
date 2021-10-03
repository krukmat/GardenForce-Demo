/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 10-03-2021
 * @last modified by  : Matias Kruk
 * Modifications Log 
 * Ver   Date         Author        Modification
 * 1.0   05-19-2021   Matias Kruk   Initial Version
**/
public with sharing class RefreshPlantParametersCallout {
    @AuraEnabled(cacheable=true)
    public static String updatePlantMoist(String plant, Integer parameter) {
        Http http = new Http();
        HttpRequest request = new HttpRequest();
         
        // Provide the Named Credentials
        request.setEndpoint('http://gardenforce.krukforce.com/rest/setup?plant_id='+plant+'&moist='+String.valueOf(parameter));
        request.setMethod('GET');        
        HttpResponse response = http.send(request);
        if (response.getStatusCode() == 200) {
            return response.getBody();
        }
        return null;
    }

    @AuraEnabled(cacheable=true)
    public static String updatePlantReadMs(String plant, Integer parameter) {
        Http http = new Http();
        HttpRequest request = new HttpRequest();
         
        // Provide the Named Credentials
        request.setEndpoint('http://gardenforce.krukforce.com/rest/setup?plant_id='+plant+'&read_ms='+String.valueOf(parameter));
        request.setMethod('GET');        
        HttpResponse response = http.send(request);
        if (response.getStatusCode() == 200) {
            return response.getBody();
        }
        return null;
    }

    @AuraEnabled(cacheable=true)
    public static String updatePlantFlowMS(String plant, Integer parameter) {
        Http http = new Http();
        HttpRequest request = new HttpRequest();
         
        // Provide the Named Credentials
        request.setEndpoint('http://gardenforce.krukforce.com/rest/setup?plant_id='+plant+'&flow_ms='+String.valueOf(parameter));
        request.setMethod('GET');        
        HttpResponse response = http.send(request);
        if (response.getStatusCode() == 200) {
            return response.getBody();
        }
        return null;
    }

    @AuraEnabled(cacheable=true)
    public static String hidrate(String plant) {
        Http http = new Http();
        HttpRequest request = new HttpRequest();
         
        // Provide the Named Credentials
        request.setEndpoint('http://gardenforce.krukforce.com/rest/hidrate?plant_id='+plant);
        request.setMethod('GET');        
        HttpResponse response = http.send(request);
        if (response.getStatusCode() == 200) {
            return response.getBody();
        }
        return null;
    }

    public static void hidrate(String plant, Integer numberOfTimes){
            for (Integer i = 0; i < numberOfTimes; i++){
                RefreshPlantParametersCallout.hidrate(plant);
            }
    }
}