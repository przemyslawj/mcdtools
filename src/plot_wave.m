electrode_index = '31';
input_file = ['out_' electrode_index '.mat'];
load(input_file);

par = set_parameters();
par.stdmin = 5;
par.stdmax = 50;
par.detect_fmin = 100;
par.detect_fmax = 10000;
par.detect_order = 4;
par.sort_fmin = 100;
par.sort_order = 4;

Get_spikes({input_file}, par);
load(['times_' input_file])

segment_start = 0;
if (~isempty(cluster_class))
    segment_start = cluster_class(1, 2) / 1000;
    segment_start = max(segment_start - 0.1, 0);
    segment_length = 120.0;
end

spike_times = cluster_class(:,2) / 1000;


x = segment_start:(1 / sr):(segment_start + segment_length);
y = data(int32(segment_start * sr):1:int32((segment_start + segment_length) * sr));
yf = spike_detection_filter(y, par);


hold;
plot(x, y);
plot(x, yf);
line_y_start = min(yf) - 0.000001;
line_y_end = min(yf) + 0.000001;


for i = 1:numel(spike_times)
    if (spike_times(i) >= segment_start) && (spike_times(i) < segment_start + segment_length)
        line([spike_times(i), spike_times(i)], [line_y_start, line_y_end], 'Color', 'black');
    end
end
