import random
import os

def generate_random_numbers(filename, num_entries, table_size):
    numbers = set()

    # Gerar números aleatórios únicos com verificação para evitar colisões por tabela
    while len(numbers) < num_entries:
        number = random.randint(1, 10 * table_size)  # Intervalo aumentado para reduzir colisões
        if number not in numbers:
            numbers.add(number)

    # Converter para lista e embaralhar para maior aleatoriedade
    numbers = list(numbers)
    random.shuffle(numbers)

    # Escrever os números no arquivo
    with open(filename, 'w') as f:
        for number in numbers:
            f.write(f"{number}\n")

def main():
    output_dir = "input_files1"
    os.makedirs(output_dir, exist_ok=True)

    table_size = 10007  # Tamanho da tabela hash, usado para ajustar intervalo de números

    configurations = [
        ("input3.txt", 1000),   
        ("input4.txt", 2000), 
        ("input5.txt", 3000), 
        ("input6.txt", 4000),
        ("input7.txt", 5000),   
        ("input8.txt", 6000),   
        ("input9.txt", 7000),   
        ("input10.txt", 8000),
        ("input11.txt", 9000),
        ("input12.txt", 10000),
        ("input13.txt", 11000),
        ("input14.txt", 12000),
        ("input15.txt", 13000),
        ("input16.txt", 14000),
        ("input17.txt", 15000),
        ("input18.txt", 16000),
        ("input19.txt", 18000),
        ("input1.txt", 20000),

    ]

    for config in configurations:
        filename, num_entries = config
        filepath = os.path.join(output_dir, filename)
        generate_random_numbers(filepath, num_entries, table_size)
        print(f"Arquivo {filename} gerado com {num_entries} entradas e sem colisões.")

if __name__ == "__main__":
    main()
