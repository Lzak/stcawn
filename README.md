## Short Text Classification Accompanying WordNet

**Current Plan:**
  1. Obtain hyponyms for each word in corpus and save into one file (taking BIG log approach)
  2. Load exported file and perform a sort to concatonate similar words
    - Place each set into an array
    - Perform sort on array *(I will be using something similar to Insertion Sort)*
      - If similarity occurs, rename unsorted word to a similar sorted word
    - Export only master words
  
**Future:**
  1. Compare multiple corpuses and determine similarities
