# pynverse

`pynverse` é uma biblioteca Python para **inversão de matrizes numéricas**
utilizando uma implementação nativa em **C** para alto desempenho.

A API é simples e expõe apenas uma função pública: `inv`.

---

## instalação
`pip install pynverse`

### uso básico
`import numpy as np`

`from pynverse import inv`

`A = np.array([
    [1, 2],
    [3, 4]
], dtype=np.float32)`

`A_inv = inv(A)`

`print(A_inv)`

das
*   Atualmente suporta float32
*   Uso interno de código nativo para computação intensiva

### performance
Em testes locais, a biblioteca consegue inverter matrizes grandes de forma eficiente (até 1000x1000), sendo adequada para fins educacionais e experimentação com algoritmos numéricos em C

Para aplicações críticas de alto desempenho, recomenda-se fortemente o uso de bibliotecas baseadas em BLAS/LAPACK (ex.: Numpy)

### limitações
*   Sem suporte a tipos esparsos
*   Sem verificação avançada de estabilidade numérica
*   Não substitui bibliotecas científicas consolidadas

### motivação
Este projeto foi desenvolvido com fins didáticos, visando:
*   Aprender a escrever extensões Python em C
*   Entender o processo de build e empacotamento (pyproject.toml, CMake)
*   Explorar desempenho numérico fora do Python puro
