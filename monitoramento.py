import subprocess
import time
import os
import statistics
import concurrent.futures
import matplotlib.pyplot as plt

def measure_execution_time(executable, input_file):
    start_time = time.perf_counter()
    try:
        subprocess.run([executable, input_file], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except subprocess.CalledProcessError as e:
        print(f"Erro ao executar {executable} com {input_file}: {e}")
        return None
    end_time = time.perf_counter()
    return end_time - start_time

def run_benchmark(executable, input_path, num_runs, warmup_runs=5):
    times = []

    # Execuções de aquecimento
    for _ in range(warmup_runs):
        measure_execution_time(executable, input_path)

    # Execuções de medição
    for _ in range(num_runs):
        exec_time = measure_execution_time(executable, input_path)
        if exec_time is not None:
            times.append(exec_time)

    if times:
        average_time = statistics.mean(times)
        median_time = statistics.median(times)
        return {
            'average': average_time,
            'median': median_time,
        }
    else:
        return None

def count_entries_in_file(file_path):
    with open(file_path, 'r') as file:
        return len(file.readlines())

def main():
    executables = {
        "Lista Encadeada": "./encadeado",
        "AVL": "./avl"
    }
    
    input_dir = "input_files3"
    input_files = [
        "input1.txt", "input2.txt" ,"input3.txt", 
        "input4.txt", "input5.txt", "input6.txt", 
        "input7.txt", "input8.txt", "input9.txt", 
        "input10.txt", "input11.txt", "input12.txt",
        "input13.txt", "input14.txt", "input15.txt",
        "input16.txt", "input17.txt", "input18.txt"
    ]
    
    num_runs = 500  # Número de execuções para medir (ajustado para um valor razoável)
    warmup_runs = 50  # Número de execuções de aquecimento
    
    results = {method: {} for method in executables.keys()}
    entry_counts = []

    for input_file in input_files:
        input_path = os.path.join(input_dir, input_file)
        entry_count = count_entries_in_file(input_path)  # Contagem do número de entradas no arquivo
        entry_counts.append(entry_count)
        
        with concurrent.futures.ThreadPoolExecutor() as executor:
            futures = {}
            for method, executable in executables.items():
                futures[method] = executor.submit(run_benchmark, executable, input_path, num_runs, warmup_runs)
            
            for method, future in futures.items():
                result = future.result()
                if result:
                    results[method][entry_count] = result
                    print(f"{method} - Entradas: {entry_count} - Média: {result['average']:.6f}s | Mediana: {result['median']:.6f}s")
                else:
                    print(f"{method} - Entradas: {entry_count} - Falha na medição.")

    # Geração de gráfico comparativo
    for metric in ['average', 'median']:
        plt.figure(figsize=(12, 6))
        for method in executables.keys():
            times = [results[method][entry_count][metric] for entry_count in entry_counts if entry_count in results[method]]
            plt.plot(entry_counts, times, marker='o', label=method)
        
        plt.xlabel('Número de Entradas')
        plt.ylabel(f'Tempo de Execução ({metric}) em segundos')
        plt.title(f'Comparação de Tempo de Execução ({metric.capitalize()}): Lista Encadeada vs AVL')
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.show()

if __name__ == "__main__":
    main()
