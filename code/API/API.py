# Te odio python, por qué tienes que existir

# https://github.com/Estacionamientos-UdeC/Backend/blob/CitreaStricta-patch-1/FabricaDeSoftware/cl/src/main.py

from fastapi import FastAPI, Request, WebSocket, WebSocketDisconnect
from pydantic import BaseModel

import asyncio
import uvicorn

app = FastAPI()

GET_SPACES = "/spaces"
WEB_SOCKET = "/socket"

# ----- #

def scanSpaces():
	scanner = open("./content/status/status.txt", 'r')
	
	return scanner.read()

# ----- #

class ConnectionManager:
	connections = None
	
	def __init__(this):
		this.connections: List[WebSocket] = []
	
	async def connect(this, socket: WebSocket):
		await socket.accept()
		
		this.connections.append(socket)
	
	async def disconnect(this, socket: WebSocket):
		this.connections.remove(socket)
	
	async def message(this, message: str, socket: WebSocket):
		await socket.send_text(message)
	
	async def broadcast(this, message: str):
		for connection in this.connections:
			await connection.send_text(message)

# ----- #

@app.websocket(WEB_SOCKET)
async def socketConnection(socket: WebSocket):
	await manager.connect(socket)
	
	try:
		while True:
			await asyncio.sleep(2)
			await socket.send_text(f"Espacios vacíos: {scanSpaces()}")
	
	except WebSocketDisconnect:
		manager.disconnect(socket)
		
		await manager.broadcast("Conexión cerrada")

@app.get(GET_SPACES)
async def getSpaces():
	spaces = scanSpaces()
	
	return {"spaces": spaces}

# ----- #

if __name__ == "__main__":
	uvicorn.run(app, host = "0.0.0.0", port = 8000)