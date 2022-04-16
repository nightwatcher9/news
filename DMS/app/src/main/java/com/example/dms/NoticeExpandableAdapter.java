package com.example.dms;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseExpandableListAdapter;
import android.widget.TextView;

import java.util.List;

public class NoticeExpandableAdapter extends BaseExpandableListAdapter {
    private List<NoticeExpandable> notices;
    private Context context;

    public NoticeExpandableAdapter(List<NoticeExpandable> notices, Context context) {
        this.notices = notices;
        this.context = context;
    }

    @Override
    public int getGroupCount() {
        return notices.size();
    }

    @Override
    public int getChildrenCount(int i) {
        return 1;
    }

    @Override
    public Object getGroup(int i) {
        return notices.get(i);
    }

    @Override
    public Object getChild(int i, int i1) {
        return notices.get(i).getContent();
    }

    @Override
    public long getGroupId(int i) {
        return 0;
    }

    @Override
    public long getChildId(int i, int i1) {
        return 0;
    }

    @Override
    public boolean hasStableIds() {
        return false;
    }

    @Override
    public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup parent) {
        View view = LayoutInflater.from(context).inflate(R.layout.notice_group,parent,false);
        NoticeExpandable notice = notices.get(groupPosition);
        TextView title = (TextView)view.findViewById(R.id.title);
        TextView time = (TextView)view.findViewById(R.id.time);
        title.setText(notice.getTitle());
        time.setText(notice.getTime());
        return view;
    }

    @Override
    public View getChildView(int groupPosition, int childPosition, boolean isLastChild, View convertView, ViewGroup parent) {
        View view = LayoutInflater.from(context).inflate(R.layout.notice_child,parent,false);
        NoticeExpandable notice = notices.get(groupPosition);
        TextView content = (TextView)view.findViewById(R.id.content);
        content.setText(notice.getContent());
        return view;
    }

    @Override
    public boolean isChildSelectable(int i, int i1) {
        return false;
    }
}
