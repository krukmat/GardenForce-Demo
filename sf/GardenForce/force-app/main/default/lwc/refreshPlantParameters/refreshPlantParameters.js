/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 06-06-2021
 * @last modified by  : Matias Kruk
 * Modifications Log 
 * Ver   Date         Author        Modification
 * 1.0   05-19-2021   Matias Kruk   Initial Version
**/
import { LightningElement, api, wire } from 'lwc';
import updateMoist from '@salesforce/apex/RefreshPlantParametersCallout.updatePlantMoist';
import updatePlantReadMs from '@salesforce/apex/RefreshPlantParametersCallout.updatePlantReadMs';
import { getRecord } from 'lightning/uiRecordApi';

const FIELDS = [
    'Plant__c.PlantId__c',
    'Plant__c.moist__c',
    'Plant__c.refresh__c'
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

    handleClick(){
       let plantLocal = this.plantId();
       let parameter = this.moist();
       // TODO: Agregar updatePlantReadMs
        updateMoist({plant: plantLocal, parameter: parameter} ).then(response => {
            // TODO: MEnsaje todo OK
            console.info('Success!!');
            parameter = this.refresh();
            updatePlantReadMs({plant: plantLocal, parameter: parameter} ).then(response => {
                // TODO: MEnsaje todo OK
                console.info('Success!!');
            }).catch(error => {
                console.log('Error: ' +error.body.message);
            });
        }).catch(error => {
            console.log('Error: ' +error.body.message);
        });
        

    }
}