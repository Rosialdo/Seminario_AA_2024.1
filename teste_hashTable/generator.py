import random

def generate_input_file(filename, num_elements, num_repeats):
    unique_elements = num_elements - num_repeats
    
    # Gerar chaves únicas para a maior parte dos elementos
    keys = [random.randint(1, 100000) for _ in range(unique_elements)]
    
    # Garantir algumas repetições ao copiar chaves já geradas
    repeated_keys = random.choices(keys, k=num_repeats)
    
    # Combinar chaves únicas com repetidas
    keys.extend(repeated_keys)
    
    # Embaralhar as chaves para que as repetidas não fiquem no final
    random.shuffle(keys)
    
    # Gerar os valores correspondentes
    values = [random.randint(1, 10000) for _ in range(num_elements)]
    
    with open(filename, 'w') as f:
        f.write(f"{num_elements}\n")
        for key, value in zip(keys, values):
            f.write(f"{key} {value}\n")


generate_input_file('input_10000.txt', 10000, 300)

generate_input_file('input_30000.txt', 30000, 1000) 

generate_input_file('input_50000.txt', 50000, 2000) 

generate_input_file('input_100000.txt', 100000, 5000) 
