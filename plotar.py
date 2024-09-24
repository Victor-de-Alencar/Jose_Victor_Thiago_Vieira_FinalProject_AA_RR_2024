import matplotlib.pyplot as plt

# Dados fornecidos
dados_normal = [1.583, 1.577, 1.615, 1.625, 1.583, 1.631, 1.581, 1.600, 1.573, 1.591]
dados_paralelo = [1.569, 1.557, 1.595, 1.557, 1.565, 1.597, 1.571, 1.599, 1.579, 1.580]

# Configurações do gráfico
plt.figure(figsize=(8, 6))
plt.plot(dados_normal, label="Normal", marker='o', linestyle='-', color='blue')
plt.plot(dados_paralelo, label="Paralelo", marker='o', linestyle='-', color='green')

# Títulos e legendas
plt.title("Comparação entre Normal e Paralelo")
plt.xlabel("Execução")
plt.ylabel("Elapsed Time")
plt.legend()

# Exibe o gráfico
plt.grid(True)
plt.show()
