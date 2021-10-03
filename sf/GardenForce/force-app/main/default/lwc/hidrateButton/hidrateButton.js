/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 10-03-2021
 * @last modified by  : Matias Kruk
**/
import { LightningElement, api, wire } from 'lwc';
import hidrate from '@salesforce/apex/RefreshPlantParametersCallout.hidrate';
import { getRecord } from 'lightning/uiRecordApi';

const FIELDS = [
    'Plant__c.PlantId__c'
];

export default class HidrateButton extends LightningElement {
    @api recordId;
    @wire(getRecord, { recordId: '$recordId', fields: FIELDS })
    plant;
    
    plantId() {
        return this.plant.data.fields.PlantId__c.value;
    }
    handleClick(){
        let plantLocal = this.plantId();
         hidrate({plant: plantLocal}).then((response) => {
            console.log(response);
        })
     }
}

//