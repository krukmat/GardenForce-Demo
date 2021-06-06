/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 05-30-2021
 * @last modified by  : Matias Kruk
 * Modifications Log 
 * Ver   Date         Author        Modification
 * 1.0   05-29-2021   Matias Kruk   Initial Version
**/
import { LightningElement, wire,api } from 'lwc';
import getMoistureHistory from '@salesforce/apex/PlanReportApex.getMoistureHistory';
import ChartJS from '@salesforce/resourceUrl/chartjs_v280';
import { loadScript } from 'lightning/platformResourceLoader';

export default class PlantReport extends LightningElement {
    @api recordId;
    allpoints = new Array();
    error;
    chart;
    chartjsInitialized = false;
    maxvalue;
    dateFieldValue;
    //configuration variable
    config = {
        type: 'line',
        data: {
            datasets: [
                {
                    data: [ ],
                    //backgroundColor: 'rgb(255, 11, 92)',
                    label: 'Moisture sensor'
                }
            ],
            labels:[],
        },
        options: {
            responsive: true,
            scales: {
                yAxes: [{
                    ticks: {
                        min: 0,
                        stepSize: 100
                    }
                }],
                xAxes: [{
                    ticks: {
                        source: 'auto',
                        min: 0,
                        stepSize: 200
                    }
                }]
            },
            legend: {
                display: false
            }
        }
    };

    handleDateChange(event){
        this.dateFieldValue = event.target.value;
        this.wiredPlant();
    }
    wiredPlant() {
        let that = this;
        getMoistureHistory({plantID: this.recordId, fecha: this.dateFieldValue}).then((data) =>{
            if (data) {
                let datalist = data;
                this.config.data.datasets[0].data.length = [];
                this.config.data.labels = [];
                this.config.data.datasets[0].data.bordercolor="rgba(119, 185, 242, 1)";
                //this.config.data.datasets[0].data.backgroundcolor="rgba(119, 185, 242, 0.2)";
                datalist.forEach(function (record){
                    that.config.data.datasets[0].data.push(record.NewValue);
                    that.config.data.labels.push(record.CreatedDate)
                });
                this.chart.update();
                this.error = undefined;
            }
        }).catch((error) =>{
            if (error) {
                this.error = error;
                this.record = undefined;
            }
        })
    }
    updateChart() {
        this.chart.update();
    }

    renderedCallback() {
        if (this.chartjsInitialized) {
            return;
        }
 
        loadScript(this, ChartJS)
            .then(() => {
                // disable Chart.js CSS injection
                window.Chart.platform.disableCSSInjection = true;
 
                const canvas = document.createElement('canvas');
                this.template.querySelector('div.chart').appendChild(canvas);
                const ctx = canvas.getContext('2d');
                this.chart = new window.Chart(ctx, this.config);
                this.wiredPlant();
            })
            .catch((error) => {
                this.error = error;
                alert(this.error);
            });
 
             
        this.chartjsInitialized = true;
    }

    
}