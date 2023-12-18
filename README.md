# Maquina Enigma

## Introducción

Simulador de dos modelos de máquina enigma:

- **Enigma Comercial (K)**: Versión comercial de la máquina, que fue exportada entre otros al bando sublevado durante la guerra civil en España. Poseía 3 ruedas (I, II, III) que se podían instalar en cualquier orden, y un único reflector configurable. 

- **Enigma Militar (M3/M4)**: Máquina usada por la Kriegsmarine. Usa 3 ruedas de un set de 8, y dos ruedas extra (las *Zusatzwalzen* **B**eta y **G**amma), que se combinan con dos reflectores (B y C).  En ciertas configuraciones, era equivalente a la máquina M3, usada por la Wehrmacht y Luftwaffe,  cuyo set era de 5 ruedas, y reflectores B y C. A diferencia del modelo comercial, los reflectores eran fijos, pero a cambio poseía un clavijero (*steckerbrett*), que intercambiaba parejas de teclas. Se usaban 10 clavijas para intercambiar 10 pares de letras.

La configuración de una máquina consta de 3 pasos:

- Selección de las ruedas: Reflector y orden de las ruedas.
- Configuración del anillo de las ruedas: Establece la referencia entre el cableado interno de las ruedas, y el anillo que marca la posición de la rueda.  Había 26 posiciones posibles para cada rueda.
- Posición de inicio: Letras que se ven por las ventanillas al iniciar el proceso de codificación/descodificación (26 posiciones por cada rueda)
- Conexión del clavijero (solo M3/M4): Intercambia la acción de pares de letras tanto en el teclado, como en las bombillas que indican la letra codificada.

En total, el **modelo K** tenía un total de **1.252.962.387.456** configuraciones posibles. Por su parte, el **modelo M3** tenía **49.649.797.445.648.384**  configuraciones, y el **modelo M4**, **4.245.426.546.133.172.224**. Aunque en la realidad varias  posiciones son *casi* equivalentes, y permitirían una decodificación parcial un mensaje.

## Compilación

    $: make

## Ejecución

    $: Enigma

Por defecto, inicializa una máquina M4 con la siguiente configuración:

    BB123[AAAA]AAAA

donde

 - BB : Reflector B, rueda extra B
 - 123: ruedas I, II y III
 - [AAAA]: Anillo para la rueda extra, y las otras ruedas
 - AAAA: Posición de inicio de la rueda extra y las otras ruedas.

La línea de comando acepta varios comandos para configurar y usar la máquina:

## Lista de acciones y comandos

### Tipo de máquina

- `tipo X`: donde X={M4 | KF | KC | KD | KS}, selecciona entre el modelos miltar, o el modelo comercial con diversos cableados de las ruedas. La máquina Enigma usada en España llevaba el cableado `KF`
- Se puede omitir `tipo` y directamente seleccionar la máquina por su tipo : `M4`, `KF`, `KC`, `KD`, `KS`.

### Modelo K
- `ruedas XXX` o `walze XXX` : con X={1|2|3}, selecciona el orden de las ruedas (*walzenlage*).
- `ring XXXX` : con X={A...Z}, configura el anillo del reflector, y de cada rueda (*ringstellung*).
- `start XXXX` o `key XXXX` : con X={A...Z}, selecciona la posición de inicio. 

### Modelo M4
- `ruedas YXXX` o `walze YXXX` : donde Y = {B|G} y X={1...8}. Selecciona el orden de las ruedas.
- `ukw X` : con X={B|C}, selecciona el reflector.
- `ring XXXX` : con X={A...Z}, configura el anillo de la rueda extra, y las otras ruedas.
- `start XXXX` o `key XXXX` : con X={A...Z}, selecciona la posición de inicio.
- `plug ABCDEF...` : Conecta dos letras en el clavijeros (*steckerbrett*). Se conectan por pares: A con B, C on D, E con F, etc...
- `unplug` : Desconecta el clavijero

**Nota**: Usando solo las ruedas 1 a 5, y con configuración de ruedas BBxxx,  anillos Axxx e inicio Axxx, es equivalente al modelo  M3 de la Wehrmacht con reflector B.       
**Nota**: Usando solo las ruedas 1 a 5, y con configuración de ruedas CGxxx,  anillos Axxx e inicio Axxx, es equivalente al modelo  M3 de la Wehrmacht con reflector C.

### Codificación

- `texto`: Modo edición para codificar un texto. Salir con `ESC`+`Return`.
- `code <texto>`: Codifica el texto.
- `fichero <filein> [fileout]`: Lee y codifica `filein`, y lo guarda en `fileout`. Si no se especifica `fileout`, entonces lo saca por pantalla (`stdout`)

Al codificar, ignora cualquier cosa que no sea un caracter {a-z} {A-Z}. Eso incluye ignorar la ñ y los números.


### Otros comandos

- `reset`: restablece ls posición de inicio.
- `salir`, `quit`,`exit` o `ctrl+d` sale del programa.
- `ayuda`, `help` o `lista` muestra la lista de comandos.
