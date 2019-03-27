/* 
 * File:   XBeeCore.h
 * Author: C0485763
 *
 * Created on 03 de Agosto de 2017, 17:00
 */

#include "UT.h"

void leMedidas(void)
{
    CCP1IE=0;
    vazaoAcumuladaMedido=freqPulses;
    horimetroMedido=tempoHorimetro;
    horimetroLigadoMedido=horimetroLigado;
    vazaoInstantaneaMedido=vazaoInstantanea;
    CCP1IE=1;
    
    vazaoAcumuladaMedido=vazaoAcumuladaMedido / 100;
    
}

uint32_t le_pulsos(void)
{
    CCP1IE=0;
    uint32_t freq=freqPulses;
    //freqPulses=0;  // Não acumula pulsos
    CCP1IE=1;
    return freq;
}

uint32_t leHorimetro(void)
{
    CCP1IE=0;
    uint32_t horimetro=tempoHorimetro;
    CCP1IE=1;
    return horimetro;
}

bool leBombaLigada(void)
{
    CCP1IE=0;
    bool bombaLigada=horimetroLigado;
    CCP1IE=1;
    return bombaLigada;
}

uint8_t leHorimetroLigado(void)
{
    CCP1IE=0;
    uint8_t horimetro=horimetroLigado;
    CCP1IE=1;
    return horimetro;
}

void inicializaVariaveis(void)
{
    TRISDbits.RD0=1;
    dig_1=PORTDbits.RD0;
    tempoHorimetro=0;
    horimetroLigado=false;
    tempoSemVazao=0;
    tempoRegistroHorimetro=0;
    tempoVazaoInstantanea=0;
    vazaoInstantanea=0;

    retornaDadosEeprom();
    freqPulsesAnterior=freqPulses;

}
