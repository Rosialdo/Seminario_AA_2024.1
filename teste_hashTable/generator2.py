"""
Como funciona:

num_repeats: Parâmetro que controla quantas repetições queremos garantir no arquivo.
unique_elements: Calcula o número de elementos únicos que serão gerados (total de elementos menos o número de repetições).
repeated_keys: Seleciona aleatoriamente algumas das chaves únicas geradas para garantir repetições.
random.shuffle(keys): Embaralha a lista de chaves para que as repetidas fiquem distribuídas aleatoriamente no arquivo.
Com essa abordagem, é possívelcontrolar quantas colisões deseja introduzir nos arquivos de entrada.

"""


import random

def generate_input_file(filename, num_elements, num_repeats):
    unique_elements = num_elements - num_repeats
    
    # Gerar chaves únicas para a maior parte dos elementos
    keys = [random.randint(1, 10000) for _ in range(unique_elements)]
    
    # Garantir algumas repetições ao copiar chaves já geradas
    repeated_keys = random.choices(keys, k=num_repeats)
    
    # Combinar chaves únicas com repetidas
    keys.extend(repeated_keys)
    
    # Embaralhar as chaves para que as repetidas não fiquem no final
    random.shuffle(keys)
    
    # Gerar os valores correspondentes
    values = [random.randint(1, 100000) for _ in range(num_elements)]
    
    with open(filename, 'w') as f:
        f.write(f"{num_elements}\n")
        for key, value in zip(keys, values):
            f.write(f"{key} {value}\n")

# Gerar arquivos de entrada para 200, 300, 400, 700 e 900 pares chave-valor
generate_input_file('input_200.txt', 200, 50)  # 50 repetições
generate_input_file('input_300.txt', 300, 75)  # 75 repetições
generate_input_file('input_400.txt', 400, 100) # 100 repetições
generate_input_file('input_700.txt', 700, 175) # 175 repetições
generate_input_file('input_900.txt', 900, 225) # 225 repetições
