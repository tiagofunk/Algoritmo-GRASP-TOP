# O que é esse repositório?

Aqui está a implementação de um algoritmo GRASP com adição de um componente Path Relinking para o problema Team Orientering Problem (TOP). Eu utilizei a linguagem C++.

Link para o artigo deste algoritmo esta [aqui](https://sbic.org.br/eventos/cbic_2021/cbic2021-166/).

# Conteúdo das pastas

- experiments: Pasta logs, script de execução e de analise dos resultados.
- instances: cenários de execução que o algoritmo será submetido.
- Irace: Pasta com configurações da ferramenta Irace. Mais informações [aqui](https://cran.r-project.org/).
- Project: Pasta com o código fonte.


# Como executar o código fonte?

Execute com:

    python pymake.py build

Vai ser criado um executável com nome de grasp, para executar:

    ./grasp 1 1 1 <instance> --alpha <a> --iterations <i> --path <y> --margin <m> --removeOperator <ro> --removePercentage <rp> --shuffleOperator <so> --addOperator <ao>

Onde:
-   instance: Arquivo com cenário de execusão.
-   a: parâmetro do GRASP que indica se será priorizada a intensificacção ou a diversificaçãoo. O intervalo de valores é [0, 1].
-   i: Números de iterações do algoritmo.
-   p: parâmetro do Path Relinking que indica o sentido da sobrescrita das soluções. Pode ser no sentido inicial para a final ou da final para a inicial.
-   ro: indica qual operador de remoção deve ser usado.
-   so: indica qual operador de embaralhamento deve ser usado.
-   ao: indica qual operador de adição deve ser usado.

Exemplo de comando de execução:

    ./grasp 1 1 1 ../instances/set_5_4/p5.4.z.txt --alpha 0.9 --iterations 5 --path y --margin 1.9 --removeOperator r --removePercentage 0.15 --shuffleOperator e --addOperator b

# Como executar um experimento?

Na pasta Scripts contém o arquivo executor.py, execute-o:

    python executor.py

O script vai executar 30 execuções de cada instância e vai salvar em um log.
