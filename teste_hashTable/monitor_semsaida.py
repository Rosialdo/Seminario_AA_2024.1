import subprocess
import time
import matplotlib.pyplot as plt

def run_external_algorithm(executable, input_file, iterations=500):
    times = []
    for _ in range(iterations):
        start_time = time.perf_counter()
        subprocess.run([f'./{executable}', input_file], check=True)
        end_time = time.perf_counter()
        times.append(end_time - start_time)
    
    return sum(times) / len(times)

def plot_comparative_graph(all_input_sizes, all_execution_times_hash, all_execution_times_on):
    plt.figure(figsize=(10, 6))
    
    # Plotar tempos de execução para a tabela hash
    plt.plot(all_input_sizes, all_execution_times_hash, marker='o', color='blue', label='Tabela Hash')

    # Plotar tempos de execução para o algoritmo O(n)
    plt.plot(all_input_sizes, all_execution_times_on, marker='o', color='green', label='Algoritmo O(n)')

    plt.xlabel('Número de Elementos')
    plt.ylabel('Tempo de Execução (segundos)')
    plt.title('Comparação de Tempo de Execução')
    plt.legend()
    plt.grid(True)
    plt.savefig('comparative_graph.png')
    plt.show()

# Nome dos executáveis (programas em C compilados)
hash_executable = 'hash_table_semsaida'
on_executable = 'on_executable'

# Lista de arquivos de entrada
input_files = ['input_10000.txt', 'input_30000.txt', 'input_50000.txt', 'input_100000.txt']

# Lista do número de elementos correspondente a cada arquivo
input_sizes = [10000, 30000, 50000, 100000]

# Armazenar os tempos de execução para cada tamanho de entrada
all_execution_times_hash = []
all_execution_times_on = []

# Executar o programa para cada tamanho de entrada e armazenar os resultados
for input_file, size in zip(input_files, input_sizes):
    exec_time_hash = run_external_algorithm(hash_executable, input_file)
    exec_time_on = run_external_algorithm(on_executable, input_file)
    
    all_execution_times_hash.append(exec_time_hash)
    all_execution_times_on.append(exec_time_on)

# Gerar o gráfico comparativo
plot_comparative_graph(input_sizes, all_execution_times_hash, all_execution_times_on)
