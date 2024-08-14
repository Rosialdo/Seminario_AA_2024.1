import subprocess
import time
import matplotlib.pyplot as plt

def run_external_algorithm(executable, input_file, output_file, iterations=5):
    times = []
    for _ in range(iterations):
        start_time = time.perf_counter()  # Usar time.perf_counter para maior precisão
        subprocess.run([f'./{executable}', input_file, output_file], check=True)
        end_time = time.perf_counter()
        times.append(end_time - start_time)
    
    # Retornar a média dos tempos de execução
    return sum(times) / len(times)

def plot_individual_graph(input_size, execution_time, all_input_sizes, all_execution_times):
    plt.figure(figsize=(10, 6))
    
    # Adiciona todos os tempos de execução para mostrar o crescimento
    plt.plot(all_input_sizes, all_execution_times, marker='o', color='blue', label='Tempo de Execução')

    # Adiciona uma linha para o tamanho da entrada atual
    plt.axvline(x=input_size, color='red', linestyle='--', label=f'Entrada {input_size}')
    
    plt.xlabel('Número de Elementos')
    plt.ylabel('Tempo de Execução (segundos)')
    plt.title(f'Crescimento do Tempo de Execução para Entrada de Tamanho {input_size}')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'graph_{input_size}.png')  # Salvar o gráfico em um arquivo
    plt.close()

# Nome do executável (o programa em C compilado)
executable = 'hash_table'

# Lista de arquivos de entrada e saída
input_files = ['input_200.txt', 'input_300.txt', 'input_400.txt', 'input_700.txt', 'input_900.txt']
output_files = ['output_200.txt', 'output_300.txt', 'output_400.txt', 'output_700.txt', 'output_900.txt']

# Lista do número de elementos correspondente a cada arquivo
input_sizes = [200, 300, 400, 700, 900]

# Armazenar os tempos de execução para cada tamanho de entrada
all_input_sizes = []
all_execution_times = []

# Adicionar execução para cada tamanho de entrada e gerar gráficos
for input_file, output_file, size in zip(input_files, output_files, input_sizes):
    exec_time = run_external_algorithm(executable, input_file, output_file)
    all_input_sizes.append(size)
    all_execution_times.append(exec_time)

# Gerar um gráfico individual para cada tamanho de entrada
for size, exec_time in zip(input_sizes, all_execution_times):
    plot_individual_graph(size, exec_time, all_input_sizes, all_execution_times)
