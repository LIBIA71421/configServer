// UPDATED
const Alexa = require('ask-sdk-core');
const AWS = require('aws-sdk');
const IotData = new AWS.IotData({endpoint: 'a16qvxfcql3rxm-ats.iot.us-east-2.amazonaws.com'});

const rootrise_0001 = {
    thingName: 'rootrise_0001',
    TurnOnPayload: '{"state": {"desired": {"WaterBomb": 1, "Buzzer": 0, "Fan": 0}}}',
    TurnOffPayload: '{"state": {"desired": {"WaterBomb": 0}}}',

    TurnOnPayloadBuzzer: '{"state": {"desired": {"WaterBomb": 0, "Buzzer": 1, "Fan": 0}}}',
    TurnOffPayloadBuzzer: '{"state": {"desired": {"Buzzer": 0}}}',

    TurnOnPayloadFan: '{"state": {"desired": {"WaterBomb": 0, "Buzzer": 0, "Fan": 1}}}',
    TurnOffPayloadFan: '{"state": {"desired": {"Fan": 0}}}',

    ShadowParams: { thingName: 'rootrise_0001' },
};

function getShadowPromise(params) {
    return new Promise((resolve, reject) => {
        IotData.getThingShadow(params, (err, data) => {
            if (err) {
                console.log(err, err.stack);
                reject(`Failed to get thing shadow ${err.errorMessage}`);
            } else {
                resolve(JSON.parse(data.payload));
            }
        });
    });
}

const LaunchRequestHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'LaunchRequest';
    },
    handle(handlerInput) {
        const speakOutput = 'Bienvenido a tu objeto inteligente Tito, ¿Qué deseas hacer?';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

/*           TURN ON - TURN OFF           */

const TurnOnIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'TurnOnIntent';
    },
    handle(handlerInput) {
        const params = {
            thingName:rootrise_0001.thingName,
            payload: rootrise_0001.TurnOnPayload
        };
        var speakOutput = "Error";
        IotData.updateThingShadow(params, function(err, data) {
            if (err) { console.log(err); }
        });

        speakOutput = 'Solicitaste encender el MOTOR!';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const TurnOffIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'TurnOffIntent';
    },
    handle(handlerInput) {
        const params = {
            thingName:rootrise_0001.thingName,
            payload: rootrise_0001.TurnOffPayload
        };
        var speakOutput = "Error";
        IotData.updateThingShadow(params, function(err, data) {
            if (err) { console.log(err); }
        });

        speakOutput = 'Solicitaste apagar el MOTOR!';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const TurnOnBuzzerIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'TurnOnBuzzerIntent';
    },
    handle(handlerInput) {
        const params = {
            thingName:rootrise_0001.thingName,
            payload: rootrise_0001.TurnOnPayloadBuzzer
        };
        var speakOutput = "Error";
        IotData.updateThingShadow(params, function(err, data) {
            if (err) { console.log(err); }
        });

        speakOutput = 'Solicitaste encender el Buzzer!';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const TurnOffBuzzerIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'TurnOffBuzzerIntent';
    },
    handle(handlerInput) {
        const params = {
            thingName:rootrise_0001.thingName,
            payload: rootrise_0001.TurnOffPayloadBuzzer
        };
        var speakOutput = "Error";
        IotData.updateThingShadow(params, function(err, data) {
            if (err) console.log(err);
        });

        speakOutput = 'Solicitaste apagar el Buzzer!';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const TurnOnFanIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'TurnOnFanIntent';
    },
    handle(handlerInput) {
        const params = {
            thingName:rootrise_0001.thingName,
            payload: rootrise_0001.TurnOnPayloadFan
        };
        var speakOutput = "Error";
        IotData.updateThingShadow(params, function(err, data) {
            if (err) { console.log(err); }
        });

        speakOutput = 'Solicitaste encender el Ventilador!';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const TurnOffFanIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'TurnOffFanIntent';
    },
    handle(handlerInput) {
        const params = {
            thingName:rootrise_0001.thingName,
            payload: rootrise_0001.TurnOffPayloadFan
        };
        var speakOutput = "Error";
        IotData.updateThingShadow(params, function(err, data) {
            if (err) console.log(err);
        });

        speakOutput = 'Solicitaste apagar el Ventilador!';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};


/*          STATES         */

const StateIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'StateIntent';
    },
    async handle(handlerInput) {
        var WaterBomb = 'unknown';
        await getShadowPromise(rootrise_0001.ShadowParams).then((result) => WaterBomb = result.state.reported.WaterBomb);
        console.log(WaterBomb);

        var speakOutput = 'Error';
        if (WaterBomb == 0) {
            speakOutput = 'el WaterBomb está apagada';
        } else if (WaterBomb == 1) {
            speakOutput = 'el WaterBomb está encendida';
        } else {
            speakOutput = 'No se pudo consultar el estado del WaterBomb, por favor intente más tarde';
        }

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const StateHumidityIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'StateHumidityIntent';
        },
    async handle(handlerInput) {
        var humedad = 'unknown';
        try {
            const result = await getShadowPromise(rootrise_0001.ShadowParams);
            if (result.state && result.state.reported && result.state.reported.humidity !== undefined) {
                humedad = result.state.reported.humidity;
            }
        } catch (err) {
            console.log('Error al obtener el shadow:', err);
        }

        var speakOutput = 'Error';
        if (humedad === 'unknown') {
            speakOutput = 'No se pudo consultar la humedad, por favor intente más tarde.';
        } else {
            speakOutput = `La humedad reportada es de ${humedad}%.`;
        }

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const StateBuzzerIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'StateBuzzerIntent';
    },
    async handle(handlerInput) {
        var Buzzer = 'unknown';
        await getShadowPromise(rootrise_0001.ShadowParams).then((result) => Buzzer = result.state.reported.Buzzer);
        console.log(Buzzer);

        var speakOutput = 'Error';
        if (Buzzer == 0) {
            speakOutput = 'el Buzzer está apagado';
        } else if (Buzzer == 1) {
            speakOutput = 'el Buzzer está encendido';
        } else {
            speakOutput = 'No se pudo consultar el estado del Buzzer, por favor intente más tarde';
        }

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const StateBoyaIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'StateBoyaIntent';
    },
    async handle(handlerInput) {
        var WaterLevel = 'unknown';
        await getShadowPromise(rootrise_0001.ShadowParams).then((result) => WaterLevel = result.state.reported.WaterLevel);
        console.log(WaterLevel);

        var speakOutput = 'Error';
        if (WaterLevel == 0) {
            speakOutput = 'el Nivel de Agua es Insuficiente';
        } else if (WaterLevel == 1) {
            speakOutput = 'el Nivel de Agua es Suficiente';
        } else {
            speakOutput = 'No se pudo consultar el estado del Buzzer, por favor intente más tarde';
        }

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};


const StateTemperatureIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'StateTemperatureIntent';
        },
    async handle(handlerInput) {
        var Temperature = 'unknown';
        try {
            const result = await getShadowPromise(rootrise_0001.ShadowParams);
            if (result.state && result.state.reported && result.state.reported.Temperature !== undefined) {
                Temperature = result.state.reported.Temperature;
            }
        } catch (err) {
            console.log('Error al obtener el shadow:', err);
        }

        var speakOutput = 'Error';
        if (Temperature === 'unknown') {
            speakOutput = 'No se pudo consultar la temperatura, por favor intente más tarde.';
        } else {
            speakOutput = `La temperatura reportada es de ${Temperature}%.`;
        }

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const StateFanIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'StateFanIntent';
    },
    async handle(handlerInput) {
        var Fan = 'unknown';
        await getShadowPromise(rootrise_0001.ShadowParams).then((result) => Fan = result.state.reported.Fan);
        console.log(Fan);

        var speakOutput = 'Error';
        if (Fan == 0) {
            speakOutput = 'el Venilador(Fan) está apagada';
        } else if (Fan == 1) {
            speakOutput = 'el Venilador(Fan) está encendida';
        } else {
            speakOutput = 'No se pudo consultar el estado del Venilador(Fan), por favor intente más tarde';
        }

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

/*      ALEXA CHANGES     */

const DeviceChangeIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'DeviceChangeIntent';
    },
    handle(handlerInput) {
        const deviceName = Alexa.getSlotValue(handlerInput.requestEnvelope, 'deviceName');
        
        // Almacena el deviceName en el contexto de la sesión
        const sessionAttributes = handlerInput.attributesManager.getSessionAttributes();
        sessionAttributes.deviceName = deviceName;
        handlerInput.attributesManager.setSessionAttributes(sessionAttributes);

        const speakOutput = `Dispositivo configurado a ${deviceName}. ¿Qué deseas hacer ahora?`;

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

/*      DEFAULT     */

const HelpIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'AMAZON.HelpIntent';
    },
    handle(handlerInput) {
        const speakOutput = 'Tienes las opciones de encender, apagar y consultar el estado, con los siguientes comandos: estadomotor, estadohumedad, estadobuzzer, estadoboya, estadotemperatura, estadoventilador, encendermotor, apagarmotor, encenderbuzzer, apagarbuzzer, encendervetilador, apagarventilador, cambiodispositivo';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const CancelAndStopIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && (Alexa.getIntentName(handlerInput.requestEnvelope) === 'AMAZON.CancelIntent'
                || Alexa.getIntentName(handlerInput.requestEnvelope) === 'AMAZON.StopIntent');
    },
    handle(handlerInput) {
        const speakOutput = 'Hasta pronto!';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .getResponse();
    }
};
/* *
 * FallbackIntent triggers when a customer says something that doesn’t map to any intents in your skill
 * It must also be defined in the language model (if the locale supports it)
 * This handler can be safely added but will be ingnored in locales that do not support it yet
 * */
const FallbackIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'AMAZON.FallbackIntent';
    },
    handle(handlerInput) {
        const speakOutput = 'Lo siento, no entendí, intenta de nuevo.';

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};
/* *
 * SessionEndedRequest notifies that a session was ended. This handler will be triggered when a currently open
 * session is closed for one of the following reasons: 1) The user says "exit" or "quit". 2) The user does not
 * respond or says something that does not match an intent defined in your voice model. 3) An error occurs
 * */
const SessionEndedRequestHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'SessionEndedRequest';
    },
    handle(handlerInput) {
        console.log(`Session ended: ${JSON.stringify(handlerInput.requestEnvelope)}`);
        // Any cleanup logic goes here.
        return handlerInput.responseBuilder.getResponse(); // notice we send an empty response
    }
};
/* *
 * The intent reflector is used for interaction model testing and debugging.
 * It will simply repeat the intent the user said. You can create custom handlers for your intents
 * by defining them above, then also adding them to the request handler chain below
 * */
const IntentReflectorHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest';
    },
    handle(handlerInput) {
        const intentName = Alexa.getIntentName(handlerInput.requestEnvelope);
        const speakOutput = `Intentó ejecutar ${intentName}`;

        return handlerInput.responseBuilder
            .speak(speakOutput)
            //.reprompt('add a reprompt if you want to keep the session open for the user to respond')
            .getResponse();
    }
};
/**
 * Generic error handling to capture any syntax or routing errors. If you receive an error
 * stating the request handler chain is not found, you have not implemented a handler for
 * the intent being invoked or included it in the skill builder below
 * */
const ErrorHandler = {
    canHandle() {
        return true;
    },
    handle(handlerInput, error) {
        const speakOutput = 'Disculpa, hubo un error. Intenta de nuevo.';
        console.log(`Error handled: ${JSON.stringify(error)}`);

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

/**
 * This handler acts as the entry point for your skill, routing all request and response
 * payloads to the handlers above. Make sure any new handlers or interceptors you've
 * defined are included below. The order matters - they're processed top to bottom
 * */
exports.handler = Alexa.SkillBuilders.custom()
    .addRequestHandlers(
        LaunchRequestHandler,

        StateIntentHandler,
        StateHumidityIntentHandler,
        StateBuzzerIntentHandler,
        StateBoyaIntentHandler,
        StateTemperatureIntentHandler,
        StateFanIntentHandler,

        TurnOnIntentHandler,
        TurnOffIntentHandler,
        TurnOnBuzzerIntentHandler,
        TurnOffBuzzerIntentHandler,
        TurnOnFanIntentHandler,
        TurnOffFanIntentHandler,

        DeviceChangeIntentHandler

/*        HelpIntentHandler,
        CancelAndStopIntentHandler,
        FallbackIntentHandler,
        SessionEndedRequestHandler
        IntentReflectorHandler*/
    )
    .addErrorHandlers(
        ErrorHandler)
    .withCustomUserAgent('sample/hello-world/v1.2')
    .lambda();

// END-UPDATED