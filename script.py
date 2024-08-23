import subprocess
import time
import os

def measure_execution_time(executable, input_file):
    start_time = time.time()
    subprocess.run([executable, input_file], check=True)
    end_time = time.time()
    return end_time - start_time

def main():
    executables = {
        "Lista Encadeada": "./hash",  # Nome do executável do código com lista encadeada
        "Árvore AVL": "./avl"  # Nome do executável do código com árvore AVL
    }
    
    input_dir = "input_files"    # Diretório dos arquivos de entrada
    input_files = [
        "input1.txt", "input2.txt", "input3.txt", 
        "input4.txt", "input5.txt", "input6.txt", 
        "input7.txt", "input8.txt", "input9.txt", 
        "input10.txt"
    ]  # Arquivos de entrada

    num_runs = 50  # Número de execuções para calcular a média

    results = { "Lista Encadeada": [], "Árvore AVL": [] }

    for input_file in input_files:
        input_path = os.path.join(input_dir, input_file)  # Caminho completo do arquivo de entrada
        
        for method, executable in executables.items():
            total_time = 0.0
            for _ in range(num_runs):
                exec_time = measure_execution_time(executable, input_path)
                total_time += exec_time
            average_time = total_time / num_runs
            results[method].append(average_time)
            print(f"{method} - Arquivo: {input_file} - Tempo médio: {average_time:.6f} segundos")

    # Geração de gráfico comparativo
    try:
        import matplotlib.pyplot as plt

        files = list(range(1, len(input_files) + 1))  # Índices dos arquivos de entrada

        plt.plot(files, results["Lista Encadeada"], marker='o', label='Lista Encadeada')
        plt.plot(files, results["Árvore AVL"], marker='o', label='Árvore AVL')

        plt.xlabel('Arquivo de Entrada (Índice)')
        plt.ylabel('Tempo Médio de Execução (s)')
        plt.title('Comparação de Tempo de Execução: Lista Encadeada vs Árvore AVL')
        plt.legend()
        plt.grid(True)
        plt.show()
    except ImportError:
        print("Matplotlib não está instalado. Gráfico não será gerado.")

if __name__ == "__main__":
    main()
