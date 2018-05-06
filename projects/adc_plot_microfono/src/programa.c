/*==================[inclusions]=============================================*/

#include "programa.h"           /* <= own header */
#include "sapi.h"               /* <= sAPI header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

//Posible implementación para reducir el ruido
/*uint16_t get_muestra(uint8_t n_samples, float sensibilidad){
	uint16_t muestrasAcumuladas=0;
	uint16_t muestraActual;
	uint8_t samplesMuestreadas;

	for(samplesMuestreadas=0; samplesMuestreadas<n_samples;samplesMuestreadas++){
		muestraActual=adcRead( CH1 );
		muestrasAcumuladas=muestrasAcumuladas+muestraActual;
	}
	uint16_t muestraModificada=muestrasAcumuladas/n_samples;
	return muestraModificada;
}*/

void inicializarVector(uint16_t vector[], uint16_t cantMuestras){
	uint16_t variableAuxiliar;
	for(variableAuxiliar=0;variableAuxiliar<cantMuestras;variableAuxiliar+1){
		vector[variableAuxiliar]=0;
	}
}
void printVector(uint16_t vector[], uint16_t cantMuestras){
	uint16_t variableAuxiliar;
	uint16_t valorActualAMostrar;
	for(variableAuxiliar=0;variableAuxiliar<cantMuestras;variableAuxiliar++){
		valorActualAMostrar=vector[variableAuxiliar];
		uartWriteByte( UART_USB, valorActualAMostrar );
	}
}

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

	/* ------------- INICIALIZACIONES ------------- */
	/* Inicializar la placa */
	boardConfig();
	/* Inicializar UART_USB a 115200 baudios */
	uartConfig( UART_USB, 115200 );
	/* Inicializar AnalogIO */
	adcConfig( ADC_ENABLE ); /* ADC */
	// Variable para almacenar el valor leido del ADC CH1
	uint16_t cantMuestras = 5; //max value = 65535 probar otros valores
	uint16_t muestras[cantMuestras];
	gpioWrite(LED2, TRUE);
	uint16_t conteoMuestras=0;


	inicializarVector(muestras, cantMuestras);
	//gpioWrite(LED2, FALSE);
	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		if(!gpioRead(TEC1)){
			gpioWrite(LED1, TRUE);
			muestras[conteoMuestras]=adcRead( CH1 );
			conteoMuestras=conteoMuestras+1;
		}
		//reinicia el conteo a 0
		if(!gpioRead(TEC2)){
			conteoMuestras=0;
			gpioWrite(LED1, FALSE);
			gpioWrite(LED2, FALSE);
		}
		//printea el valor por la uart_usb
		if(!gpioRead(TEC3)){
			printVector(muestras, cantMuestras);
		}
	}
	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
	  por ningun S.O. */
	return 0 ;
}

/*==================[end of file]============================================*/
