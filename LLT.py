import numpy as np
import itertools

def unique_permutations_two(n):
    # Generate the list that contains pairs of numbers from 2 to n-1
    num_list = [i for i in range(2, n) for _ in (0, 1)]
    num_list.append(1)
    num_list.append(n)

    # Use a set to keep track of unique permutations
    unique_perms_set = set()

    # Generate permutations excluding 1 and n as they will be fixed in the first and last positions
    for perm in itertools.permutations(num_list):
        # Create a full permutation by adding 1 at the start and n at the end
        full_perm = (1,) + perm + (n,)

        # Add the full permutation as a tuple to the set to ensure uniqueness

        flag = True

        # Check the colored triangle condition
        for i in range(0, n):
            count = 0 
            for j in range (0,2*i+1):
                if full_perm[j] == i+1:
                    count += 1
            
            if count != 1:
                flag = False
                break

        if flag:
            unique_perms_set.add(full_perm)

    # Convert the set back to a list of lists
    unique_perms_list = [list(perm) for perm in unique_perms_set]

    return unique_perms_list

def find_positions(full_perm, i):
    return [pos for pos, num in enumerate(full_perm) if num == i]

def unique_permutations_three(n, perm_two):
    #Here perm_two must be a valid permutation with 2 levels

    # Generate the list that contains triplets of numbers from 2 to n-1
    num_list = [i for i in range(2, n) for _ in (0, 1, 2)]
    num_list.append(1)
    num_list.append(1)
    num_list.append(n)
    num_list.append(n)

    # Use a set to keep track of unique permutations
    unique_perms_set = set()

    # Generate permutations excluding 1 and n as they will be fixed in the first and last positions
    for perm in itertools.permutations(num_list):
        # Create a full permutation by adding 1 at the start and n at the end
        full_perm = (1,) + perm + (n,)

        flag = True

        # Check the colored triangle condition
        for i in range(1, n+1):
            pos3 = find_positions(full_perm, i)
            pos2 = find_positions(perm_two, i)

            if not (pos3[0] <= pos2[0] + np.floor(pos2[0]/2) < pos3[1] <= pos2[1] + np.floor(pos2[1]/2) < pos3[2]):
                flag = False
                break

        if flag:
            unique_perms_set.add(full_perm)

    # Convert the set back to a list of lists
    unique_perms_list = [list(perm) for perm in unique_perms_set]

    return unique_perms_list

n=4

counter = 0
combined_list = []

unique_two = unique_permutations_two(n)
print(len(unique_two))

f = open('depth3_colors' + str(n) + '.txt', 'w')

for perm in unique_two:
    counter += 1
    added_three = unique_permutations_three(n, perm)
    combined_list.extend(added_three)
    f.write("\n========================\n")
    print(counter, " of ", len(unique_two), " - consists of ", len(added_three), " - permutation ", perm)
    print("========================")
    for k in range(len(added_three)):
        # print(added_three[k])
        f.write(str(added_three[k]) + "\n   ")
        for kk in range(len(perm)):
            f.write(str(perm[kk]) + ", ")
            if(kk%2==1):
                f.write("   ")
        # print("---")
        f.write("\n---\n")

# print(combined_list)
print(len(combined_list))
