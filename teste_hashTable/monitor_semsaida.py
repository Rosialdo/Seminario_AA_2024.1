import subprocess
import time
import matplotlib.pyplot as plt

def run_external_algorithm(executable, input_file, iterations=500):
    times = []
    for _ in range(iterations):
        start_time = time.perf_counter()
        subprocess.run([f'./{executable}', input_file], check=True)  # Removido o argumento de saída
        end_time = time.perf_counter()
        times.append(end_time - start_time)
    
    return sum(times) / len(times)

def plot_comparative_graph(all_input_sizes, all_execution_times):
    plt.figure(figsize=(10, 6))
    
    # Plotar todos os tempos de execução para mostrar o crescimento
    plt.plot(all_input_sizes, all_execution_times, marker='o', color='blue', label='Tempo de Execução')

    plt.xlabel('Número de Elementos')
    plt.ylabel('Tempo de Execução (segundos)')
    plt.title('Crescimento do Tempo de Execução')
    plt.legend()
    plt.grid(True)
    plt.savefig('comparative_graph.png')  # Salvar o gráfico em um arquivo
    plt.show()

# Nome do executável (o programa em C compilado)
executable = 'hash_table_semsaida'

# Lista de arquivos de entrada
input_files = ['input_1000.txt', 'input_3000.txt', 'input_5000.txt', 'input_10000.txt']

# Lista do número de elementos correspondente a cada arquivo
input_sizes = [1000, 3000, 5000, 10000]

# Armazenar os tempos de execução para cada tamanho de entrada
all_input_sizes = []
all_execution_times = []

# Executar o programa para cada tamanho de entrada e armazenar os resultados
for input_file, size in zip(input_files, input_sizes):
    exec_time = run_external_algorithm(executable, input_file)
    all_input_sizes.append(size)
    all_execution_times.append(exec_time)

# Gerar o gráfico comparativo
plot_comparative_graph(all_input_sizes, all_execution_times)
