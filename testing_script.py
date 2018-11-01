import os as os
from subprocess import Popen, PIPE,check_call
import sys
print(sys.version)
max_jitd_val =10**9
max_jitd_size =10**9
threshold_list = [10**6,10**7,10**8]
policy_act_for = [1,2,3,4,5,6,7,8,9,10,20]
no_of_scans = 1000
#crack only act for
for threshold in threshold_list:
    steps_for_current_exp = [x * (10 ** 8 / threshold) for x in policy_act_for]
    print(steps_for_current_exp)
    for nooftransforms in steps_for_current_exp:
          # print(nooftransforms)
        commond_str_act_for = (['init random %s %s' % (max_jitd_size, max_jitd_val), "dump", "gen_scan %s %s" % (no_of_scans, max_jitd_val),
        "policy_set crack %s" % threshold, "policy_act_for %s"%nooftransforms, "dump", "random_scan"])

        with open('./output/crack_%s_%s.txt'%(threshold,nooftransforms), 'w') as out, Popen(["./driver", "-j", "-"], stdin=PIPE, stdout=out,
                                                            stderr=out) as proc:
            for cmd in commond_str_act_for:
                # print(cmd)
                proc.stdin.write(bytes(cmd, 'utf-8') + b"\n")

            proc.stdin.close()

for threshold in threshold_list:
    # for nooftransforms in policy_act_for:
        commond_str_act_for = (['init random %s %s' % (max_jitd_size, max_jitd_val), "dump", "gen_scan %s %s" % (no_of_scans, max_jitd_val),
        "policy_set crack %s" % threshold, "policy_act_until_done", "dump", "random_scan"])

        with open('./output/crack_until_done_%s.txt'%(threshold), 'w') as out, Popen(["./driver", "-j", "-"], stdin=PIPE, stdout=out,
                                                            stderr=out) as proc:
            for cmd in commond_str_act_for:
                # print(cmd)
                proc.stdin.write(bytes(cmd, 'utf-8') + b"\n")

            proc.stdin.close()
#crack sort act for
for threshold in threshold_list:
    steps_for_current_exp = [x * (10 ** 8 / threshold) for x in policy_act_for]
    for nooftransforms in steps_for_current_exp:
        commond_str_act_for = (['init random %s %s' % (max_jitd_size, max_jitd_val), "dump", "gen_scan %s %s" % (no_of_scans, max_jitd_val),
        "policy_set crack %s" % threshold, "policy_act_until_done %s", "dump","policy_set sort %s" % threshold, "policy_act_for %s"%nooftransforms, "dump", "random_scan"])

        with open('./output/cracksort_%s_%s.txt'%(threshold,nooftransforms), 'w') as out, Popen(["./driver", "-j", "-"], stdin=PIPE, stdout=out,
                                                            stderr=out) as proc:
            for cmd in commond_str_act_for:
                # print(cmd)
                proc.stdin.write(bytes(cmd, 'utf-8') + b"\n")

            proc.stdin.close()
for threshold in threshold_list:
    # for nooftransforms in policy_act_for:
        commond_str_act_for = (['init random %s %s' % (max_jitd_size, max_jitd_val), "dump", "gen_scan %s %s" % (no_of_scans, max_jitd_val),
        "policy_set crack %s" % threshold, "policy_act_until_done %s", "dump","policy_set sort %s" % threshold, "policy_act_until_done", "dump", "random_scan"])

        with open('./output/cracksort_until_done_%s.txt'%(threshold), 'w') as out, Popen(["./driver", "-j", "-"], stdin=PIPE, stdout=out,
                                                            stderr=out) as proc:
            for cmd in commond_str_act_for:
                # print(cmd)
                proc.stdin.write(bytes(cmd, 'utf-8') + b"\n")

            proc.stdin.close()
#crack sort merge act for
for threshold in threshold_list:
    steps_for_current_exp = [x * (10 ** 8 / threshold) for x in policy_act_for]
    for nooftransforms in steps_for_current_exp:
        commond_str_act_for = (['init random %s %s' % (max_jitd_size, max_jitd_val), "dump", "gen_scan %s %s" % (no_of_scans, max_jitd_val),
        "policy_set crack %s" % threshold, "policy_act_until_done", "dump","policy_set sort %s" % threshold, "policy_act_until_done", "dump",
                                "policy_set merge %s" % threshold, "merge_act_for %s"%nooftransforms, "dump", "random_scan"])

        with open('./output/cracksortmerge_%s_%s.txt'%(threshold,nooftransforms), 'w') as out, Popen(["./driver", "-j", "-"], stdin=PIPE, stdout=out,
                                                            stderr=out) as proc:
            for cmd in commond_str_act_for:
                # print(cmd)
                proc.stdin.write(bytes(cmd, 'utf-8') + b"\n")

            proc.stdin.close()
for threshold in threshold_list:
    # for nooftransforms in policy_act_for:
        commond_str_act_for = (
        ['init random %s %s' % (max_jitd_size, max_jitd_val), "dump", "gen_scan %s %s" % (no_of_scans, max_jitd_val),
         "policy_set crack %s" % threshold, "policy_act_until_done", "dump",
         "policy_set sort %s" % threshold, "policy_act_until_done", "dump",
         "policy_set merge %s" % threshold, "merge_act_until_done", "dump", "random_scan"])

        with open('./output/cracksortmerge_until_done_%s.txt' % (threshold), 'w') as out, Popen(
                ["./driver", "-j", "-"], stdin=PIPE, stdout=out,
                stderr=out) as proc:
            for cmd in commond_str_act_for:
                # print(cmd)
                proc.stdin.write(bytes(cmd, 'utf-8') + b"\n")

            proc.stdin.close()



