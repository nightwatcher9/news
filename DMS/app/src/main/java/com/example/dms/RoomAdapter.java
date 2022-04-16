package com.example.dms;

import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class RoomAdapter extends RecyclerView.Adapter<RoomAdapter.ItemViewHolder> {
    private List<Room> roomList;
    private String buildId;
    public RoomAdapter(List<Room> roomList) {
        this.roomList = roomList;
        buildId= roomList.get(0).getRoomNumber().substring(0,1);
    }

    @NonNull
    @Override
    public ItemViewHolder onCreateViewHolder(@NonNull final ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.room, parent, false);
        final ItemViewHolder itemViewHolder = new ItemViewHolder(view); //新加final
        itemViewHolder.roomPic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(parent.getContext(), AdminRoomInformation.class);
                intent.putExtra("roomNumber",buildId+itemViewHolder.roomNumber.getText() );
                parent.getContext().startActivity(intent);
            }
        });
        return itemViewHolder;
    }

    @Override
    public void onBindViewHolder(@NonNull ItemViewHolder holder, int position) {
        Room room = roomList.get(position);
        holder.roomNumber.setText(Integer.toString(Integer.parseInt(room.getRoomNumber())%1000));
        holder.roomPic.setImageResource(room.getPicId());
    }

    @Override
    public int getItemCount() {
        return roomList.size();
    }


    static class ItemViewHolder extends RecyclerView.ViewHolder {
        private TextView roomNumber;
        private ImageView roomPic;

        public ItemViewHolder(View itemView) {
            super(itemView);
            roomNumber = (TextView) itemView.findViewById(R.id.roomNumber);
            roomPic = (ImageView) itemView.findViewById(R.id.roomPic);
        }
    }

}
