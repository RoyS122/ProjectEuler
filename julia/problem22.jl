alphabet_dict = Dict{Char, Int}()

# Populate the dictionary with alphabet characters and their corresponding indices
for (i, char) in enumerate("abcdefghijklmnopqrstuvwxyz")
    alphabet_dict[char] = i 
end

function getAlphabetScore(word) # Get the score alphabetical of the word
    score = 0;
    for char in lowercase(word)
        score += alphabet_dict[char]
    end
    return score
end

function importWordListFromFile(path)  #Open the file and parse it to get only the words in an array
    buffer = read(path::AbstractString, String)
    wordlist = []
    current_w = false
    word = ""
    for c in buffer
        if c == '"' 
            if current_w && length(word) > 0 
                push!(wordlist, word)
                word = ""
            else
                current_w = true
            end
        elseif c != ',' 
            word = word *""* c
        end
    end
    return wordlist
end

function getTotalScoreOfNameList(path)  # Calcul the words and multiply it by his own position and calcul the total
    list = importWordListFromFile(path)    
    scores = []
    sort!(list)
    for w in list 
        push!(scores, getAlphabetScore(w))
    end
    scores = scores
    totscore = 0
    for (i, s) in enumerate(scores)
        totscore += i * s
    end
    return totscore
end


println(getTotalScoreOfNameList("data/0022_names.txt"))
