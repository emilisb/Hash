# Custom hash algorithm

![version][version-badge]

 ## [Task](https://github.com/blockchain-group/Blockchain-technologijos/blob/master/pratybos/1uzduotis-Hashavimas.md)
 
 ## How to run
 - `https://github.com/emilisb/Hash.git`
 - `cd Hash`
 - `make`
 - `./bin/uzduotis <arg1> <arg>`
 
 ## Usage
 - Benchmark test: `<program> benchmark <filename>`
 - Usage with string: `<program> <string>`
 - Usage with file: `<program> file <filename>`
 
 ## Results
 1. Hash length is always the same, e.g.:
 - Lietuva - `33oip9edxwvnxvo0j2zqfe3r209sffl9`
 - LietuvaTevyneMusu - `v8i2o6a66apy6glhgqag78b9a7f1mwb5`
 2. Hashing time of konstitucija.txt - 0.003842s
 3. Time comparison with SHA256:
 ```
 Starting comparison with SHA256 with 100000 strings of 14 characters
 My hash took: 0.171999s
 SHA256 took: 0.215976s
 ```
 4. Word collision test:
 ```
 Starting word collision test with 1000000 pairs of 5 characters
 Collisions found in word test: 0
 ```
 5. Similar word collision test (when only 1 character is different):
 ```
 Starting similar word collision test with 100000 pairs of 5 characters
 Collisions found in similar words test: 0
 Minimum difference: 23.8281
 Maximum difference: 48.0469
 Average difference: 35.6871
 ```
 
 6. Results of [hashrank by @dqmis](https://github.com/dqmis/hashrank):
 ```
 Reference SHA test took: 5.3863s.
 Average hashing time of Konstitucija: 0.0035s.
 
 Letter collision test took: 804.7102s.
 Letter similarity average: 0.0108
 Found 0 collision(s)
 
 Word collision test took: 820.5668s.
 Word similarity average: 0.0108
 Found 0 collision(s)
 ```

[version-badge]: https://img.shields.io/badge/version-0.1-green.svg
