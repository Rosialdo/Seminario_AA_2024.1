import random

def generate_input_file(filename, num_elements, repeat_probability=0.1):
    keys = []
    with open(filename, 'w') as f:
        f.write(f"{num_elements}\n")
        for i in range(num_elements):
            if keys and random.random() < repeat_probability:
                key = random.choice(keys)  # Reutiliza uma chave já existente
            else:
                key = random.randint(1, 10000)
                keys.append(key)  # Armazena a nova chave

            value = random.randint(1, 100000)
            f.write(f"{key} {value}\n")

# Gerar arquivos de entrada para diferentes quantidades de pares chave-valor
generate_input_file('input_500.txt', 500, repeat_probability=0.1)
generate_input_file('input_1000.txt', 1000, repeat_probability=0.15)
generate_input_file('input_1500.txt', 1500, repeat_probability=0.2)
generate_input_file('input_2000.txt', 2000, repeat_probability=0.25)

