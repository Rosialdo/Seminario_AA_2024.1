import random
import os

def generate_random_numbers(filename, num_entries, num_collisions):
    numbers = set()

    # Gerar números aleatórios únicos
    while len(numbers) < num_entries - num_collisions:
        number = random.randint(1, 1000000)
        numbers.add(number)

    # Converter para lista para facilitar a manipulação
    numbers = list(numbers)

    # Adicionar colisões aleatórias
    for _ in range(num_collisions):
        colliding_number = random.choice(numbers)
        numbers.append(colliding_number)

    # Embaralhar a lista para que as colisões estejam distribuídas aleatoriamente
    random.shuffle(numbers)

    # Escrever os números no arquivo
    with open(filename, 'w') as f:
        for number in numbers:
            f.write(f"{number}\n")

def main():
    output_dir = "input_files"
    os.makedirs(output_dir, exist_ok=True)

    # Configurações para os arquivos de entrada
    configurations = [
        ("input1.txt", 50, 5),     
        ("input2.txt", 100, 10),   
        ("input3.txt", 1000, 50),   
        ("input4.txt", 2000, 100), 
        ("input5.txt", 3000, 150), 
        ("input6.txt", 4000, 200),
        ("input7.txt", 5000, 250),   
        ("input8.txt", 6000, 300),   
        ("input9.txt", 7000, 350),   
        ("input10.txt", 8000, 400),  
        ("input11.txt", 9000, 450),   
        ("input12.txt", 10000, 500),
    ]

    for config in configurations:
        filename, num_entries, num_collisions = config
        filepath = os.path.join(output_dir, filename)
        generate_random_numbers(filepath, num_entries, num_collisions)
        print(f"Arquivo {filename} gerado com {num_entries} entradas e {num_collisions} colisões.")

if __name__ == "__main__":
    main()
