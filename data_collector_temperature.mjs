import { DynamoDBDocumentClient, PutCommand } from "@aws-sdk/lib-dynamodb";
import { DynamoDBClient } from "@aws-sdk/client-dynamodb";

const client = new DynamoDBClient({});
const docClient = DynamoDBDocumentClient.from(client);

export const handler = async (event) => {
    console.log("Evento recibido:", JSON.stringify(event, null, 2));

    const command = new PutCommand({
        TableName: "rootrise_data2",
        Item: {
            timestamp: event.timestamp?.toString() || new Date().toISOString(), // Convertir a string o usar fecha actual
            thing_name: event.thing_name,
            sn: event.sn,
            Temperature: event.Temperature,
        },
    });

    try {
        const response = await docClient.send(command);
        console.log("Respuesta de DynamoDB:", response);
    } catch (error) {
        console.error("Error al insertar en DynamoDB:", error);
    }
};


//REGLA IMPLEMENTADA PARA 
/*
Instrucción SQL
SELECT timestamp() AS timestamp, topic(3) AS thing_name, substring(topic(3), 9) AS sn, state.reported.Temperature AS Temperature FROM '$aws/things/+/shadow/update/accepted' WHERE substring(topic(3), 0, 8) = 'rootrise' AND state.reported.Temperature > 0
*/