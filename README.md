# Backend del proyecto de estacionamientos UdeC

## Dependencias

1. C++ STL
2. OpenCV

### Sobre OpenCV

Si usan Arch Linux hay un paquete llamado "opencv" y según recuerdo también existe uno en distribuciones basadas en Debian.

* [Documentación](https://docs.opencv.org/4.8.0/index.html)
* [Instrucciones de instalación](https://docs.opencv.org/4.8.0/df/d65/tutorial_table_of_content_introduction.html)

## Estructura del proyecto

* `code`: En esta carpeta va todo el código del proyecto.
	* `API`: Código que se encarga de recibir solicitudes y enviar información del servidor a los clientes.
	* `server`: Código que se encarga de manejar y recopilar información sobre el estado del estacionamiento.
	* `test`: Código temporal para probar el funcionamiento de versiones preliminares y/o funcionalidades específicas de la aplicacion pero que no serán en sí mismas parte del resultado final.

* `content`: Todo el contenido que será accesado desde el código del proyecto.
	* `images`: Imágenes que deben ser procesadas por el servidor.
	* `labels`: Etiquetas de los objetos en los datasets.
	* `models`: Modelos de YOLO con formato ONNX que serán usados para procesar las imágenes.

* `exec`: Ejecutables y archivos de compilación del proyecto.