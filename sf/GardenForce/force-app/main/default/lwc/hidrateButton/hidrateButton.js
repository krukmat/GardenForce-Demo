/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 09-14-2021
 * @last modified by  : Matias Kruk
**/
import { LightningElement } from 'lwc';

export default class HidrateButton extends LightningElement {
    handleClick(){
         fetch('https://hidrate.ngrok.io/hidrate', // End point URL
        {method:"GET"}).then((response) => {
            return response.json(); // returning the response in the form of JSON
        })
     }
}

//