import requests
import numpy as np

tourist_spots = {
    "Torre Eiffel": (48.858844, 2.294351),
    "Museu do Louvre": (48.860611, 2.337644),
    "Catedral de Notre-Dame": (48.852968, 2.349902),
    "Arco do Triunfo": (48.873792, 2.295028),
    "Palácio de Versalhes": (48.804865, 2.120355),
    "Basílica de Sacré-Cœur": (48.886707, 2.343104),
    "Museu d'Orsay": (48.860006, 2.326606),
    "Jardim de Luxemburgo": (48.846222, 2.337160),
    "Place de la Concorde": (48.865633, 2.321236),
    "Panteão": (48.846222, 2.345868)
}

# URL base do GraphHopper API
graphhopper_url = "https://graphhopper.com/api/1/route"
api_key = "GRAPHHOPER_API_KEY"

def save_matrix_to_file(matrix, filename):
    with open(filename, "w") as f:
        for row in matrix:
            row_str = " ".join(f"{value:.5f}" for value in row)
            f.write(row_str + "\n")
    print(f"Matriz salva em {filename}")

# Função para obter o tempo de viagem entre dois pontos de bicicleta
def get_bike_travel_time(lat1, lon1, lat2, lon2):
    if not lat1 or not lon1 or not lat2 or not lon2:
        print(f"Erro: Um ou mais pontos são inválidos.")
        return None

    params = {
        "point": [f"{lat1},{lon1}", f"{lat2},{lon2}"],
        "vehicle": "bike",  # Modo de transporte: bicicleta
        "locale": "en",
        "key": api_key
    }

    response = requests.get(graphhopper_url, params=params)

    if response.status_code == 200:
        data = response.json()
        return data['paths'][0]['time'] / 1000  # Converter para segundos
    else:
        print(f"Erro: {response.status_code}, Mensagem: {response.text}")
        return None

# Criar matriz de tempos de viagem para bicicleta
n = len(tourist_spots)
tourist_spots_list = list(tourist_spots.keys())
matrix_bike = np.zeros((n, n))

for i in range(n):
    for j in range(n):
        if i != j:
            lat1, lon1 = tourist_spots[tourist_spots_list[i]]
            lat2, lon2 = tourist_spots[tourist_spots_list[j]]
            time_bike = get_bike_travel_time(lat1, lon1, lat2, lon2)
            if time_bike is not None:
                matrix_bike[i][j] = time_bike

# Exibir e salvar a matriz de tempos de viagem para bicicleta
print("Matriz de tempos de viagem (Bicicleta) [segundos]:")
print(matrix_bike)
save_matrix_to_file(matrix_bike, "bike_matrix.txt")
