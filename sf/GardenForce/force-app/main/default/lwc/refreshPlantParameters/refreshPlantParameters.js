/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 06-12-2021
 * @last modified by  : Matias Kruk
 * Modifications Log 
 * Ver   Date         Author        Modification
 * 1.0   05-19-2021   Matias Kruk   Initial Version
**/
import { LightningElement, api, wire } from 'lwc';
import updateMoist from '@salesforce/apex/RefreshPlantParametersCallout.updatePlantMoist';
import updatePlantReadMs from '@salesforce/apex/RefreshPlantParametersCallout.updatePlantReadMs';
import updatePlantFlowMS from '@salesforce/apex/RefreshPlantParametersCallout.updatePlantFlowMS';
import { getRecord } from 'lightning/uiRecordApi';

const FIELDS = [
    'Plant__c.PlantId__c',
    'Plant__c.moist__c',
    'Plant__c.refresh__c',
    'Plant__c.flowMS__c'
];

export default class RefreshPlantParameters extends LightningElement {
    @api recordId;
    @wire(getRecord, { recordId: '$recordId', fields: FIELDS })
    plant;
    
    plantId() {
        return this.plant.data.fields.PlantId__c.value;
    }

    moist() {
        return this.plant.data.fields.moist__c.value;
    }

    refresh() {
        return this.plant.data.fields.refresh__c.value;
    }

    flowMS() {
        return this.plant.data.fields.flowMS__c.value;
    }

    handleClick(){
       let plantLocal = this.plantId();
       let moist = this.moist();
       let refresh = this.refresh();
       let flowMS = this.flowMS();
        Promise.all([updateMoist({plant: plantLocal, parameter: moist} ), updatePlantReadMs({plant: plantLocal, parameter: refresh} ), updatePlantFlowMS({plant: plantLocal, parameter: flowMS})]).then(response => {
            // TODO: MEnsaje todo OK
            console.info(response);     
        }).catch(error => {
            console.log('Error: ' +error.body.message);
        });
        

    }
}