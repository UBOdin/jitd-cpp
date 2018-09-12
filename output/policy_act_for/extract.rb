

File.open("timing.csv", "w+") do |output|
  output.puts ["Experiment", "Init_Time", "Action_Count", "Action_Time", "Scan_Time"].join(",")
  Dir["policy_act*"].sort.each do |source|
    data = File.open(source) { |f| f.read }
    # puts "----------------"
    # puts source
    # puts data

    raise "A" unless /Init JITD: ([0-9]+) us/ =~ data 
    init_time = $1.to_i

    raise "B" unless /.olicy_act[^ ]* ([0-9]+) Actions: ([.0-9+\-e]+) us/ =~ data
    actions = $1.to_i
    act_time = $2.to_f

    raise "C" unless /Scan JITD time in Random Mode: ([.0-9+\-e]+) us/ =~ data
    scan_time = $1.to_f


    output.puts [source, init_time, actions, act_time, scan_time].join(",")
  end
end